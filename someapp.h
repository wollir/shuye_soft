#ifndef SOMEAPP_H
#define SOMEAPP_H
#include<QString>
#include<QTableWidget>

typedef struct
{
    uchar tempL;
    uchar tempH;
    uchar humiL;
    uchar humiH;
}sht_data;
typedef struct {
    uchar id;
    QVector<uchar> channle_addr; //结点，信道地址
    QVector<uchar> activat_cmd; //CCD传感器数据请求指令
    QVector<uchar> call_cmd;    //下位机登记指令
    uchar received_data[60];    //CCD传感器数据
    QString received_time;      //接收时间
    bool isexist;               //节点登记结果
    float liq_height = 0;       //液面高度
    double temprature; //温湿度
    double Humidity; //温湿度
}terminal_struct;


void show_error();
unsigned char data_aver(unsigned char* data, int size);
void MyDelay(unsigned int msec);
QString get_time();
void DataTOTableView(QTableWidget * tab, terminal_struct *term);
void terminal_disconnected(QTableWidget *tab,terminal_struct *term);
void cal_TempHumi(sht_data data,double &temp,double &humi);
#endif // SOMEAPP_H
