#ifndef SOMEAPP_H
#define SOMEAPP_H
#include<QString>
#include<QTableWidget>
#include<QVector>
#include"database.h"
typedef unsigned short u16;
class QLabel;

static QVector<uchar> active_key{69,82,0,0,0,50,0,15,66,64,0,0};  //控制 ICG SH的积分时间
static QVector<uchar> addr{0x00,0x00,0x17};  // 两字节地址，1字节目标信道
static QVector<uchar> call_terminal{69,82,1,1,1,1,1,1,1,1,1,1}; //召唤下位机，收到回复说明存在

typedef struct
{
    uchar tempL;
    uchar tempH;
    uchar humiL;
    uchar humiH;
}sht_data;
class terminal_struct{
public:
    unsigned short id;
    unsigned char addr_channle[3]; //结点，信道地址
    QVector<uchar> activat_cmd; //CCD传感器数据请求指令
    QVector<uchar> call_cmd;    //下位机登记指令
    uchar received_data[60];    //CCD传感器数据
    QString received_time;      //接收时间
    bool isexist;               //节点登记结果
    float liq_height;       //液面高度
    double temprature; //温湿度
    double Humidity; //温湿度
    bool isAlarm;  //是否需要报警
    QString api_key;
    QString device_id;
    //int hang; //在tableWidget的第几行

    terminal_struct(u16 a):id(a){
        call_cmd =call_terminal;
        call_cmd[2] = a>>8;
        call_cmd[3] = a&0xff;

        activat_cmd = active_key;
        activat_cmd[10] = a>>8; //id先发高位，再发低位
        activat_cmd[11] = a&0xff;

        addr_channle[0] = a>>8;//地址高字节，没用
        addr_channle[1] = a;//地址低字节，= id
        addr_channle[2] = 0x17;//信道,全用这个
        received_time = "";
        isexist = 0;
        temprature = 0.0;
        Humidity = 0.0;
        liq_height = 0.0;
        isAlarm = false;
    }
    explicit terminal_struct(){}
};


void show_error();
unsigned char data_aver(unsigned char* data, int size);
void MyDelay(unsigned int msec);
QString get_time();
void DataTOTableView(QTableWidget * tab, terminal_struct *term);  //当本节点的信息来到时的操作
void initTableView(QTableWidget *tab,QList<terminal_struct> *Nodes);//根据数据库中的节点信息来初始化表
int LineInTableWidget(QTableWidget *tab,u16 id);//节点id对应的是tablewidget的第几行

void terminal_disconnected(QTableWidget *tab,terminal_struct *term);  //当节点没有回应时候的操作
void cal_TempHumi(sht_data data,double &temp,double &humi);
QList<terminal_struct> ::iterator which_node(u16 id, QList<terminal_struct> *Nodes); //找id对应的节点迭代器
void flashAlarm(QLabel * lab,bool flash);
#endif // SOMEAPP_H
