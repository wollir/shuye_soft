#ifndef SOMEAPP_H
#define SOMEAPP_H
#include<QString>
#include<QTableWidget>
#include<QVector>
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
    uchar id;
    // QVector<uchar> addr;        //Lora地址
    QVector<uchar> channle_addr; //结点，信道地址
    QVector<uchar> activat_cmd; //CCD传感器数据请求指令
    QVector<uchar> call_cmd;    //下位机登记指令
    uchar received_data[60];    //CCD传感器数据
    QString received_time;      //接收时间
    bool isexist;               //节点登记结果
    float liq_height = 0;       //液面高度
    double temprature; //温湿度
    double Humidity; //温湿度
//public:
    terminal_struct(uchar a):id(a){
       call_cmd =call_terminal;
       call_cmd[2] = a;
       activat_cmd = active_key;
       activat_cmd[10] = a;
       channle_addr = addr;
       channle_addr[1] = a-1;
       received_time = "";
       isexist = 0;
    }
    explicit terminal_struct(){}
};


void show_error();
unsigned char data_aver(unsigned char* data, int size);
void MyDelay(unsigned int msec);
QString get_time();
void DataTOTableView(QTableWidget * tab, terminal_struct *term);
void terminal_disconnected(QTableWidget *tab,terminal_struct *term);
void cal_TempHumi(sht_data data,double &temp,double &humi);
QVector<unsigned char> initNode(QString filename);
#endif // SOMEAPP_H
