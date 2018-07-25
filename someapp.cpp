#include"someapp.h"
#include<QSerialPort>
#include<QMessageBox>
#include<QTime>
#include<QCoreApplication>
#include<QTableWidgetItem>
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
{
    ;
}
QString get_time()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    //QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");    //yyyy表示年；MM表示月；dd表示日； hh表示小时；mm表示分；ss表示秒；zzz表示毫秒；ddd表示周几
    QString current_date =current_date_time.toString("MM/dd hh:mm:ss");    //yyyy表示年；MM表示月；dd表示日； hh表示小时；mm表示分；ss表示秒；zzz表示毫秒；ddd表示周几
    return current_date;
}
void terminal_disconnected(QTableWidget *tab,terminal_struct *term)
{
    tab->setItem(term->id-1 ,2,new QTableWidgetItem(QIcon(":/red_led.png"), "掉线"));
}
void DataTOTableView(QTableWidget *tab, terminal_struct *term)
{
    //QTableWidgetItem *vHeader5 = new QTableWidgetItem;
    //vHeader5->setIcon(QIcon(":/led.png"));
    //tab->setVerticalHeaderItem(0, vHeader5);
    tab->setItem(term->id -1,1,new QTableWidgetItem(QString::number(term->liq_height,'f',1)+"mm"));
    tab->setItem(term->id-1 ,2,new QTableWidgetItem(QIcon(":/led.png"), "在线"));
    tab->setItem(term->id-1,3,new QTableWidgetItem(term->received_time));
    tab->setItem(term->id-1,4,new QTableWidgetItem(QString::number(term->temprature, 10, 1)));
    tab->setItem(term->id-1,5,new QTableWidgetItem(QString::number(term->Humidity, 10, 1)));
    //tab->setItem(0,1,new QTableWidgetItem(QIcon("led.png"), "Jan's month"));

    //    QTableWidgetItem *item5_0 = new QTableWidgetItem;
    //    QTableWidgetItem *item5_1 = new QTableWidgetItem;
    //    item5_0->setText(QString("%1").arg(5));
    //    item5_1->setText(QString("%1").arg(5));
    //    tab->setItem(0, 0, item5_0);
    //    tab->setItem(0, 1, item5_1);
    //tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
