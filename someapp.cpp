#include"someapp.h"
#include<QSerialPort>
#include<QMessageBox>
#include<QTime>
#include<QCoreApplication>
#include<QTableWidgetItem>
#include<QLabel>
#include<QMovie>
extern QSerialPort serial;
void MyDelay(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
/* 当串口打开失败，提示错误*/
void show_error()
{
    QMessageBox *msgBox;
    msgBox = new QMessageBox("错误",		        ///--这里是设置消息框标题
                             "串口打开失败",						///--这里是设置消息框显示的内容
                             QMessageBox::Critical,							///--这里是在消息框显示的图标
                             QMessageBox::Ok | QMessageBox::Default,		///---这里是显示消息框上的按钮情况
                             QMessageBox::Cancel | QMessageBox::Escape,	///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
                             0);														///---这里是 定义第三个按钮， 该例子 只是 了显示2个按钮

    msgBox->show();									///---显示消息框

}
/* 计算接收数据的平均值*/
unsigned char data_aver(unsigned char* data, int size)
{
    unsigned long temp = 0;
    for(int i = 0;i < size; i++)
    {
        temp+=data[i];
    }
    return temp/60;
}
void get_terminal_num(void)
{}
QString get_time()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    //QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");    //yyyy表示年；MM表示月；dd表示日； hh表示小时；mm表示分；ss表示秒；zzz表示毫秒；ddd表示周几
    QString current_date =current_date_time.toString("MM/dd hh:mm:ss");    //yyyy表示年；MM表示月；dd表示日； hh表示小时；mm表示分；ss表示秒；zzz表示毫秒；ddd表示周几
    return current_date;
}
void terminal_disconnected(QTableWidget *tab,terminal_struct *term)
{
   int hang = LineInTableWidget(tab,term->id);
    tab->setItem(hang ,2,new QTableWidgetItem(QIcon(":/gray_led.png"), "掉线"));
}
void initTableView(QTableWidget *tab,QList<terminal_struct> *Nodes)
{
    QList<terminal_struct>::iterator ite = Nodes->begin();
    int i = 0;
    for( ;ite != Nodes->end();ite++){
        int rowIndex = tab->rowCount();
        tab->setRowCount(rowIndex + 1);//总行数增加1
        tab->setItem(i,0,new QTableWidgetItem(QString::number(ite->id)));
        tab->setItem(i,1,new QTableWidgetItem(QString::number(ite->liq_height,'f',1)+"mm"));
        tab->setItem(i,2,new QTableWidgetItem(QIcon(":/gray_led.png"), "离线"));
        tab->setItem(i,3,new QTableWidgetItem(ite->received_time));
        tab->setItem(i,4,new QTableWidgetItem(QString::number(ite->temprature, 10, 1)));
        tab->setItem(i,5,new QTableWidgetItem(QString::number(ite->Humidity, 10, 1)));
        i++;
    }
}
void DataTOTableView(QTableWidget *tab, terminal_struct *term)
{
    //找出在第几行
   int hang = LineInTableWidget(tab,term->id);
    tab->setItem(hang,1,new QTableWidgetItem(QString::number(term->liq_height,'f',1)+"mm"));
    if(!term->isAlarm)
        tab->setItem(hang,2,new QTableWidgetItem(QIcon(":/led.png"), "在线"));
    else
        tab->setItem(hang,2,new QTableWidgetItem(QIcon(":/red_led.png"), "警告"));
    tab->setItem(hang,3,new QTableWidgetItem(term->received_time));
    tab->setItem(hang,4,new QTableWidgetItem(QString::number(term->temprature, 10, 1)));
    tab->setItem(hang,5,new QTableWidgetItem(QString::number(term->Humidity, 10, 1)));
}
// 计算真是的温湿度
void cal_TempHumi(sht_data data,double &temp,double &humi)
{
    unsigned short temp_raw = 0 ,humi_raw = 0;
    temp_raw = data.tempH<<8;
    temp_raw |=data.tempL;
    humi_raw = data.humiH<<8;
    humi_raw |=data.humiL;
    temp = -45+175.0*temp_raw/65535;
    humi = 100.0*humi_raw/65535;
}

int LineInTableWidget(QTableWidget *tab, u16 id)
{
    int i = 0;
    for(; i < tab->rowCount();i++){
        int num = tab->item(i,0)->text().toInt();//取出字符串
        if(id == num)
            break;
    }
    return i;
}

QList<terminal_struct> ::iterator which_node(u16 id, QList<terminal_struct> *Nodes)
{
    QList<terminal_struct> ::iterator ite = nullptr;
    for(ite = Nodes->begin();ite != Nodes->end();ite++){
        if(id == ite->id)
            return ite;
    }
    return ite;
}

void flashAlarm(QLabel * lab,bool flash)
{
    QMovie *movie = new QMovie("alarm.gif");
    lab->setMovie(movie);
    if(flash)
        movie->start();
    else
        movie->stop();
}
