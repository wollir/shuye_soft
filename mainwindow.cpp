#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDesktopWidget>
#include<QTime>
#include"signin.h"
#include"database.h"
#include"onenet_http.h"
//#define wireless 1

const int real_receive_size = 60;
const int used_pixel = 60;
double view_re[used_pixel];       // kalman 滤波以后的数据
//unsigned char sorted_60data[used_pixel];
unsigned char dou2uchar[real_receive_size];
sht_data temp_humi;
unsigned char  yuzhi = 0;
uchar min_position = 0;
u16 current_row = 0; //当前tablewigit的行数
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
  ,Nodes(new QList<terminal_struct>)
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
        ui->comboBox_2->addItem("无端口");
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
    static int numReadTotal = 0;
    numReadTotal += qa.length();
    //qDebug ()<< numReadTotal;
    if(numReadTotal == 2 + real_receive_size  + 4 + 2 + 1+1)   //接收固定的 俩帧头 + 60个字节  +温湿度+ 终端号 + 是否报警了+预留 = 70
    {
        ui->label_4->setText(QString::number(re.length()));  //显示接收的长度
        //QString current_text = ui->textEdit_2->toPlainText();
        //ui->textEdit_2->setText(current_text + re.toHex());
        if((re[0] == 0xfe) && (re[1] == 0x01))//数据
        {
            recieve_succeed = 1;   //按钮事件等待这个标志来处理信息
            //qDebug() << "recieve_succeed";
            re.remove(0,2); //去帧头
        }
        else if((re[0] == 0xff) && (re[1] == 0x02))//回应，call terminal
        {
            //qDebug() <<"recieve from id:"<< (uint8_t)re[2]*256+(uint8_t)re[3];
            if((uint8_t)re[2]*256+(uint8_t)re[3] == Ite_cur->id )//确认是当前终端的数据
                Ite_cur->isexist = true;
            re = 0;
        }
        numReadTotal = 0;
        serial.clear();
    }
    timer.start();
}
void MainWindow::timeout_()  // 100ms 一次
{
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
    ui->qwtPlot_2->setTitle("液面数据");
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
    for(int i = 0; i < used_pixel; i++){
        view_re [i] =  (double)whichtoDisplay->received_data[i];
    }
    ui->Thermo->setValue(whichtoDisplay->liq_height);
    ui->label_8->setText(QString::number(whichtoDisplay->liq_height, 10, 1)+"MM");
    curve.setPen(QPen(Qt::yellow));//设置画笔
    x_falling[0] = x_falling[1] = min_position;
    curve.setSamples(x_falling,y_falling,2);  // 标志下降沿
    // ----------------------- 存储数据到文本
    //save_data(dou2uchar,used_pixel);
    ui->textEdit_2->setText(prepare_str_for_textview(whichtoDisplay->received_data,used_pixel));
    curve_2.setSamples(pixel1,view_re,used_pixel);
    curve_2.attach(ui->qwtPlot_2);
    curve.attach(ui->qwtPlot_2);
    ui->qwtPlot_2->replot();
}
void MainWindow::data_process()
{
    int i;
    for( i= 0; i < used_pixel; i++){            //
        dou2uchar[i] =  (uchar)re[i];
    }
    //i++;
    temp_humi.tempL = re[i++];temp_humi.tempH = re[i++];
    temp_humi.humiL = re[i++];temp_humi.humiH = re[i++];
    //SortFrom3648(dou2uchar,sorted_60data,used_pixel);       //挑出60个数据；
    calmanfilter.shift_win_filter(dou2uchar,used_pixel);      // 滑动窗滤波
    re.clear();
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

        serial.setBaudRate(QSerialPort::Baud9600);  //波特率
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
    QList<terminal_struct> ::iterator ite =Nodes->begin();
    for(; ite != Nodes->end();ite++)
    {
        qDebug() <<"term:"<<ite->id;
        Ite_cur = ite;
        ite->isexist = false;
#ifdef wireless
        serial.write((const char*)ite->addr_channle,3);
#endif
        serial.write((const char*)ite->call_cmd.begin(),12);

        //实现延时2s与等待时间发生两个其中之一
        QTime _Timer = QTime::currentTime().addMSecs(3000);
        while( QTime::currentTime() < _Timer && !ite->isexist)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        if(ite->isexist){
            qDebug()<<"exist!";
            DataTOTableView(ui->tableWidget,&(*ite)); //更新表格
            ui->comboBox_3->addItem(QString::number(ite->id));
        }
        //延时一会，避免相互影响
        _Timer = QTime::currentTime().addMSecs(100);
        while( QTime::currentTime() < _Timer)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
void MainWindow::on_pushButton_5_clicked()   //扫描
{
    if(serial.isOpen()){
        ui->comboBox_3->clear();
        ui->groupBox_2->setDisabled(true);
        call_for_terminal();
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
    whichtoDisplay = which_node(arg1.toInt(),Nodes);
}
void MainWindow::active()
{
    bool isAlarm = false;
    ui->pushButton_3->setDisabled(true);
    static int all_data_times = 0;
    all_data_times++;
    QList<terminal_struct> ::iterator ite =Nodes->begin();
    for(; ite != Nodes->end(); ite++)
    {
        Ite_cur = ite;
        if(!ite->isexist)//当前节点不存在
            continue;
        recieve_succeed = 0;
        serial.clear();
#ifdef wireless
        serial.write((const char*)ite->addr_channle,3);
#endif
        serial.write((const char*)ite->activat_cmd.begin(),12);

        QTime _Timer = QTime::currentTime().addMSecs(3000);
        while( QTime::currentTime() < _Timer && !recieve_succeed)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        if(recieve_succeed == 1){
            //qDebug() << "最晚接收时间为："<< _Timer <<' '<<"现在时间："<<QTime::currentTime();
            data_process();
            things_todo_after_received(&(*ite)); //相当于Ite_cur
            if(ite->isAlarm){
                isAlarm = true;
                flashAlarm(ui->label_9,true);
            }
        }
        else{
            static int diubao = 0;
            terminal_disconnected(ui->tableWidget,&(*ite));
            qDebug() <<"lost:"<<++diubao<<"/"<<all_data_times;
            re.clear();
        }
        //延时一会，避免相互影响
        _Timer = QTime::currentTime().addMSecs(100);
        while( QTime::currentTime() < _Timer)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    ui->pushButton_3->setDisabled(false);
    flashAlarm(ui->label_9,isAlarm);
}
// 将对应终端的信息设置成接受到的信息。
void MainWindow::things_todo_after_received(terminal_struct *term)
{
    for(int i =0;i<used_pixel;i++)
        term->received_data[i] =dou2uchar[i];
    cal_TempHumi(temp_humi,term->temprature,term->Humidity); //计算温湿度
    //qDebug()<<"湿度："<< term->Humidity<<" 温度："<< term->temprature <<endl;
    min_position = calmanfilter.find_min1(term->received_data,used_pixel);
    //qDebug()<< min_position <<endl;
    term->liq_height =  calmanfilter.liquid_pos(min_position);
    term->isAlarm = (term->liq_height <= 10)? true:false;//是否需要报警
    //alarmOrnot(term,ui->tableWidget);
    term->received_time = get_time();
    DataTOTableView(ui->tableWidget,term); //表格显示
    if(&(*whichtoDisplay) == term)
        curve_update();
    if(term->device_id.size()){ //在云上有
        //http_post->run(term->device_id,term->api_key,term->temprature,term->Humidity,term->liq_height);
//        QThread *mythread = new QThread;
//        onenet_http *temp = new onenet_http(term->device_id,term->api_key,term->temprature,term->Humidity,term->liq_height);
//        temp->moveToThread(mythread);
//        connect(mythread, SIGNAL(started()), temp, SLOT(run()));
//        mythread->start();

        onenet_http *temp = new onenet_http(term->device_id,term->api_key,term->temprature,term->Humidity,term->liq_height);
        temp->start();
    }
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
//    QPalette palette;
//    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/background.png")));
//    this->setPalette(palette);
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
    //ui->tableWidget->verticalHeader()->setStretchLastSection(true); //垂直是否铺满

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    //ui->tableWidget->setItem(0,0,new QTableWidgetItem("1"));

    //连接数据库,初始化终端
    databasehandle = Database::getDatabaseP();
    if(!databasehandle->isopen() && !databasehandle->creat_sql_connection())
        return ;
    QList<u16> term_id = databasehandle->get_lastNodes();
    //QString filePath =  "./node_info/node_info.txt";
    //auto term_id = initNode(filePath);
    QList<u16>::iterator ite = term_id.begin();
    for(; ite != term_id.end();ite++){
        auto temp = terminal_struct(*ite);
        //初始化节点的device_id 和 api_key
        auto deviceid_api = databasehandle->get_device_info(temp.id);
        temp.device_id = deviceid_api.first;
        temp.api_key = deviceid_api.second;
        Nodes->push_back(temp);
    }
    initTableView(ui->tableWidget,Nodes);
    // 刚开始 关闭串口，激活，自动激活 都应失效。
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->spinBox->setDisabled(true);
    ui->groupBox_2->setDisabled(true);
    curve_init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeout_()));
    timer.start(100);
    for(int i = 0;i < real_receive_size;i++)     {  pixel1[i] = i;   }//初始化曲线坐标
}
//终端管理
void MainWindow::on_pushButton_6_clicked()
{
    SignIn *si = new SignIn(Nodes,ui->tableWidget,ui->comboBox_3);
    si->show();

}
//双击 tablewidget
void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    int id = ui->tableWidget->item(row,0)->text().toInt();
    qDebug() << id;
    whichtoDisplay =  which_node(id,Nodes);
    curve_update();
}
