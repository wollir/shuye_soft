#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDesktopWidget>
#define wireless

#define real_receive_size 60
#define used_pixel 60
double view_re[used_pixel];       // kalman 滤波以后的数据
//unsigned char sorted_60data[used_pixel];
unsigned char dou2uchar[real_receive_size];
sht_data temp_humi;
unsigned char  yuzhi = 0;
uchar min_position = 0;
uchar current_row = 0; //当前tablewigit的行数
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sys_init();
}
void MainWindow::initSeialPort()
{
    infos = QSerialPortInfo::availablePorts();
    //获取计算机上所有串口并添加到comboBox中
    if(infos.isEmpty())
    {
        ui->comboBox_2->addItem("无串口");
        return;
    }
    if (infos.size() != last_infos.size()){
        ui->comboBox_2->clear();
        foreach (QSerialPortInfo info, infos) {
            ui->comboBox_2->addItem(info.portName());
            //qDebug() << info.portName();
        }
    }
    last_infos = infos;
}
void MainWindow::serialRead()    // 这里有可能将两帧数据各取一段当做一帧；
{
    timer.stop();  // 读串口的时候关掉定时器，以免受到影响。
    QByteArray qa = serial.readAll();
    re.append(qa);
    numReadTotal += qa.length();
    if(numReadTotal == 2 + real_receive_size + 1 + 4)   //接收固定的 俩帧头 + 60个字节 + 终端号 +温湿度
    {
        //int lable_val = ui->label_4->text().toInt();
        ui->label_4->setText(QString::number(re.length()));  //显示接收的长度
        //qDebug()<<re;
        //QString current_text = ui->textEdit_2->toPlainText();
        //ui->textEdit_2->setText(current_text + re.toHex());
        if((re[0] == 0xfe) && (re[1] == 0x01))//判断帧头
        {
            whose_data =re[real_receive_size+2+4];//[62]
            recieve_succeed = 1;   //按钮事件等待这个标志来处理信息
            re.remove(0,2); //去帧头
            //re.remove(62,1);//去掉最后一字节
            data_process();
           // curve_update();
        }
        else if((re[0] == 0xff) && (re[1] == 0x02))//判断响应的帧头
        {
            terminal[re[2]-1]->isexist = 1;
        }
        re = 0;
        numReadTotal = 0;
        serial.clear();
    }
    timer.start();
}
void MainWindow::timeout_()  // 100ms 一次
{
    timer_divide++;
    if(aoto_active_statues){ //如果是激活状态
        timer_divide_active++;

        if (timer_divide_active == flash_secend/2)
            ui->label_7->setText("0");
        if(timer_divide_active == flash_secend*10){
            QPixmap icon(":/led.png");
            ui->label_7->setPixmap(icon);
            active();
            timer_divide_active = 0;
        }
    }
    else
    {
        timer_divide_active = 0;//将计数清零
    }
}
void MainWindow::curve_init()
{
    ui->qwtPlot_2->setTitle("CCD 数据");
    ui->qwtPlot_2->setCanvasBackground(Qt::gray);
    ui->qwtPlot_2->setAxisScale( QwtPlot::yLeft, 100, 200.0);
    //绘制横坐标标度
    ui->qwtPlot_2->setAxisScale( QwtPlot::xBottom, 0.0, 65.0);

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3) );//设置样本点的颜色、大小
    curve_2.setSymbol(symbol);//添加样本点形状
    //curve.setCurveAttribute(QwtPlotCurve::Fitted, true);//使曲线更光滑，不加这句曲线会很硬朗，有折点
    curve_2.setPen(QPen(Qt::red));//设置画笔
    curve_2.setSamples(pixel,gray_value,10);
    //    //加到plot，plot由IDE创建
    curve_2.attach(ui->qwtPlot_2);
    QwtPlotGrid *grid = new QwtPlotGrid;//网格
    grid->enableXMin(true);
    grid->setMajorPen(QPen(Qt::white, 0, Qt::DotLine));//大格子
    grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));//大格子里的小格子
    grid->attach(ui->qwtPlot_2);
}
void MainWindow::curve_update()
{
    for(int i = 0; i < used_pixel; i++){            // 卡尔曼滤波
        view_re [i] =  (double)terminal[whose_data-1]->received_data[i];
    }
    curve.setPen(QPen(Qt::yellow));//设置画笔
    x_falling[0] = x_falling[1] = min_position;
    curve.setSamples(x_falling,y_falling,2);  // 标志下降沿
    // ----------------------- 存储数据到文本
    save_data(dou2uchar,used_pixel);
    ui->textEdit_2->setText(prepare_str_for_textview(dou2uchar,used_pixel));
    // curve_2.setSamples((double)falling,pixel1);
    //    curve.setSamples(pixel1,view_re,real_receive_size);
    //    curve.attach(ui->qwtPlot);
    //    ui->qwtPlot->replot();
    curve_2.setSamples(pixel1,view_re,used_pixel);
    curve_2.attach(ui->qwtPlot_2);
    curve.attach(ui->qwtPlot_2);
    ui->qwtPlot_2->replot();
    re = 0;
}
void MainWindow::data_process()
{
    int i;
    for( i= 0; i < used_pixel; i++){            //
        dou2uchar[i] =  (uchar)re[i];
    }
    //i++;
    temp_humi.tempL = re[i++];temp_humi.tempH = re[i++];temp_humi.humiL = re[i++];temp_humi.humiH = re[i++];
    //SortFrom3648(dou2uchar,sorted_60data,used_pixel);       //挑出60个数据；
    calmanfilter.shift_win_filter(dou2uchar,used_pixel);                 // 滑动窗滤波
//    for(int i = 0; i < used_pixel; i++){            // 卡尔曼滤波
//         terminal[whose_data-1]->received_data[i] = dou2uchar[i];
//    }

    //qDebug()<< "平均值："<<data_aver(dou2uchar,used_pixel);
    //qDebug()<< "最小点："<<min_position;
}
//---------------------------- 串口号改变
void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    int i = 0;
    foreach (info, infos) {
        if(info.portName() == arg1) break;
        i++;
    }
    if(i != infos.size ()){//can find

        serial.setBaudRate(QSerialPort::Baud115200);  //波特率
        //              serial.setDataBits(QSerialPort::Data8);     //数据位
        //              serial.setParity(QSerialPort::NoParity);    //无奇偶校验
        //              serial.setStopBits(QSerialPort::OneStop);   //无停止位
        //              serial.setFlowControl(QSerialPort::NoFlowControl);  //无控制
    }
}

void MainWindow::on_pushButton_3_clicked()   //激活按钮
{   active();}
void MainWindow::on_pushButton_clicked()// 打开串口
{
    serial.close();
    serial.setPort(info);
    serial.open(QIODevice::ReadWrite);          //读写打开
    if(!serial.isOpen())
        show_error();
    else{
        ui->groupBox_2->setEnabled(true);
        ui->refresh_b->setDisabled(true);
        ui->spinBox->setEnabled(true);
        ui->comboBox->setDisabled(true);
        ui->comboBox_2->setDisabled(true);
        ui->pushButton->setEnabled(false); //串口打开了，打开串口按钮失效
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);

    }
}
void MainWindow::on_pushButton_2_clicked()// 关闭串口
{
    serial.clear();
    serial.close();
    if(aoto_active_statues) //如果自动激活没关
        emit ui->pushButton_4->clicked(true);
    ui->groupBox_2->setDisabled(true);
    ui->spinBox->setEnabled(false);
    ui->comboBox->setDisabled(false);
    ui->comboBox_2->setDisabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
    ui->pushButton_3->setEnabled(false); //关闭了串口，激活，自动激活按钮都失效
    ui->pushButton_4->setEnabled(false);
    ui->refresh_b->setDisabled(false);
}
void MainWindow::on_clear_receive_clicked()
{
    ui->textEdit_2->setText(""); ui->label_4->setText("0");
}
void MainWindow::on_pushButton_4_clicked() //自动激活
{
    aoto_active_statues = !aoto_active_statues;
    if(aoto_active_statues)//激活
    {
        ui->pushButton_3->setEnabled(false); //自动激活的时候，手动激活失效
        ui->spinBox->setDisabled(true); //激活状态不允许更改秒数；
        ui->pushButton_5->setDisabled(true);//扫描
        ui->comboBox_3->setDisabled(true); //显示终端号

        ui->pushButton_4->setText("取消激活");
        flash_secend = ui->spinBox->value();
    }
    else
    {
        ui->pushButton_3->setEnabled(true);//手动激活使能。
        ui->spinBox->setDisabled(false); //不是激活状态才允许更改秒数；
        ui->pushButton_5->setDisabled(false);
        ui->comboBox_3->setDisabled(false);

        ui->pushButton_4->setText("自动激活");
    }
}
void MainWindow::call_for_terminal() //这里发，serialread 收
{
    for(int i = 0; i < max_terminal_num; i++){
        // call_terminal[2] = i;  //将召唤数据的第三位，改为编号 1-6
#ifdef wireless
        serial.write((const char*)terminal[i]->channle_addr.begin(),3);
#endif
        serial.write((const char*)terminal[i]->call_cmd.begin(),12);
        MyDelay(2000);
        if(terminal[i]->isexist){
            ui->comboBox_3->addItem(QString::number(i+1));
        }
    }
}
void MainWindow::on_pushButton_5_clicked()   //扫描
{
    if(serial.isOpen()){
        ui->comboBox_3->clear();
        //ui->pushButton_5->setDisabled(true);
        ui->groupBox_2->setDisabled(true);
        call_for_terminal();
        //ui->pushButton_5->setDisabled(false);
        ui->groupBox_2->setDisabled(false);
        serial.clear();
    }
    else
        show_error();
}
void MainWindow::on_refresh_b_clicked()
{
    initSeialPort();
}
void MainWindow::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    active_key[10] = arg1.toInt();
}
void MainWindow::active()
{
    ui->pushButton_3->setDisabled(true);
    for(int i= 0; i< max_terminal_num;i++)
    {
        recieve_succeed = 0;
        if(terminal[i]->isexist){    //节点已经注册的话
#ifdef wireless
            serial.write((const char*)terminal[i]->channle_addr.begin(),3);
#endif
            serial.write((const char*)terminal[i]->activat_cmd.begin(),12);
            MyDelay(2000);
            if(recieve_succeed == 1)
                things_todo_after_received(terminal[i]);
            else
                terminal_disconnected(ui->tableWidget,terminal[i]);
        }
    }
    ui->pushButton_3->setDisabled(false);
}
// 将对应终端的信息设置成接受到的信息。
void MainWindow::things_todo_after_received(terminal_struct *term)
{
    for(int i =0;i<used_pixel;i++)
        term->received_data[i] =dou2uchar[i];
    cal_TempHumi(temp_humi,term->temprature,term->Humidity); //计算温湿度
    qDebug()<<"湿度："<< term->Humidity<<" 温度："<< term->temprature <<endl;
    min_position = calmanfilter.find_min1(term->received_data,used_pixel);
    //qDebug()<< min_position <<endl;

    term->liq_height =  calmanfilter.liquid_pos(min_position);
    ui->Thermo->setValue(term->liq_height);
    ui->label_8->setText(QString::number(term->liq_height, 10, 1)+"MM");
    term->received_time = get_time();
    DataTOTableView(ui->tableWidget,term); //表格显示
    curve_update();
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
   if(index == 0)      serial.setBaudRate(QSerialPort::Baud115200);
   else                serial.setBaudRate(QSerialPort::Baud9600);
}
void MainWindow::sys_init()
{
    this->setWindowIcon(QIcon(":/sia.jpg"));
    //-------------设置窗体背景
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/background.png")));
    this->setPalette(palette);
    QIcon icon(":/refresh.png");
    ui->refresh_b->setIcon(icon);
    ui->refresh_b->setIconSize(QSize(20,20));
    //---------------设置 TextEdit 的背景
    QPalette palette_text = ui->textEdit_2->palette();
    //palette_text.setColor(QPalette::Background,Qt::gray);    //设置颜色
    palette_text.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    // palette_text.setbrush(QPalette::Background,QBrush(....));     //设置图片
    ui->textEdit_2->setPalette(palette_text);
    initSeialPort();
    connect(&serial,SIGNAL(readyRead()),this,SLOT(serialRead()));   //连接槽
    // 设置表格
    //ui->tableWidget->setRowCount(5);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setStretchLastSection(true);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    //ui->tableWidget->setItem(0,0,new QTableWidgetItem("1"));

    // 刚开始 关闭串口，激活，自动激活 都应失效。
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->spinBox->setDisabled(true);
    ui->groupBox_2->setDisabled(true);
    curve_init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeout_()));
    //timer.setInterval();
    timer.start(100);
    for(int i = 0;i<real_receive_size;i++)     {  pixel1[i] = i;   }//初始化曲线坐标
    for(int i = 0;i<max_terminal_num;i++)
    {
        terminal.append(new terminal_struct);
        //terminal[i] = new terminal_struct; //申请节点空间
        call_terminal[2] = i+1;
        terminal[i]->call_cmd = call_terminal;

        active_key[10] = i+1;
        terminal[i]->activat_cmd = active_key;
        addr[1] = i;
        terminal[i]->channle_addr = addr;
        //terminal[i]->received_data = 0;
        terminal[i]->received_time = "";
        terminal[i]->isexist = 0;
        terminal[i]->id = i+1;
    }
}


