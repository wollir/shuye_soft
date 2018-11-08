#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include<QIODevice>
#include<QTimer>

#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include<qwt_legend.h>
#include <qwt_symbol.h>

#include "calman.h"
#include"someapp.h"
#include<QDebug>
#include<QByteArray>
#include<QComboBox>
#include<QTableWidgetItem>
#include<QList>

//前置类声明
class Database ;
class onenet_http;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() {  delete ui;    }
    QSerialPort serial;//串口实例
    QList<QSerialPortInfo> infos;
    QList<QSerialPortInfo> last_infos;
    void sys_init();
    void initSeialPort();//初始化串口函数
    void curve_init();
    void curve_update();
    void data_process();
    void active();
    void things_todo_after_received(terminal_struct* term);
    QSerialPortInfo info;
private slots:
    void serialRead();
    void timeout_();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_clear_receive_clicked();
    //void QComboBox::mousePressEvent(QMouseEvent * event);
    void on_pushButton_4_clicked();
    void call_for_terminal();
    void on_pushButton_5_clicked();

    void on_refresh_b_clicked();
    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_6_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

signals:
    void add_com();

private:
    Ui::MainWindow *ui;
    //uchar after_send_time = 0; //记录发送以后的时间，如果长时间不回复，说明掉线了
    QByteArray re;
    unsigned char recieve_succeed = 0;
    QTimer timer;
    QwtPlotCurve curve; // 下降沿那条线
    QwtPlotCurve curve_2;
    //bool activate_flag = 0;// 标志是否激活更新曲线
    QwtPlotGrid *grid;               //网格
    //  terminal[max_terminal_num];//终端结构体指针
    //QVector<terminal_struct*> terminal;//(max_terminal_num,nullptr);
    //QVector<uchar> active_key{69,82,0,0,0,50,0,15,66,64,0,0};  //控制 ICG SH的积分时间
    //QVector<uchar> addr{0x00,0x00,0x17};  // 两字节地址，1字节目标信道
    //QVector<uchar> call_terminal{69,82,1,1,1,1,1,1,1,1,1,1}; //召唤下位机，收到回复说明存在

    //bool exit_flag[max_terminal_num] = {0,0,0,0,0};  //第几位表示第几个节点为1。
    //X轴
    double pixel[10] = {0, 5, 9,10, 14,25,36,38,50,52};
    double pixel1[3648] = {0};
    //Y轴数据
    double gray_value[10] = {123, 145, 251, 189, 245, 110, 211, 129, 165,210};
    //  画下降沿的那条标志线，，，
    double x_falling[2];
    double y_falling[2] = {5,200};

    QPolygonF points;
    calman calmanfilter;
    // 自动激活
    bool aoto_active_statues = 0; //自动激活 按键的状态
    int flash_secend = 2;//刷新的秒数
    int timer_divide_active = 0;
    //测试下位机存在与否
    QList<terminal_struct> *Nodes;
    Database *databasehandle;
    QList<terminal_struct> ::iterator Ite_cur;
    QList<terminal_struct> ::iterator whichtoDisplay;
};
#endif // MAINWINDOW_H
