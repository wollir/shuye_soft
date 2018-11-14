#ifndef ONENET_HTTP_H
#define ONENET_HTTP_H
#include <QMainWindow>
#include<QObject>
#include <QThread>
#include<QMutex>
#include<QMutexLocker>


const QString ZHUCE_url  = "http://api.heclouds.com/devices";
const QString DELETE_URL = "http://api.heclouds.com/devices/";
const QString MASTER_APIKEY = "9FAQQOyzwZp=0qAgdy3YILp80aE=";
const QString ZHUCE_PROTOCAL = "MQTT";


class QNetworkAccessManager;
class QNetworkReply;
//更新数据用
class onenetPostData:public QThread
{
    Q_OBJECT
private:
    QNetworkAccessManager *nam;
    QNetworkReply* reply;

    QString device_id;
    QString api_key;
    float temp;
    float humidity;
    float liquid_hight;

private slots:
    void post_finishedSlot(QNetworkReply *reply);

signals:
    void all_job_done();
public:
    onenetPostData(QString p_device_id,QString p_api_key,float p_temp,float p_humidity,float p_liquid_hight);
    ~onenetPostData(){
        delete nam;
        delete reply;
    }
    void post_data();
    void run();
    static QMutex mut;
};
//------------------------------------------------------------
enum functionType{
  DeleteTerm = 0,
  AddNewTerm = 1
};
class createNewDevice:public QThread
{
    Q_OBJECT
public:
    createNewDevice(functionType type,QString devicename);
    void run();
    void getNewDevice();
    void DeleteDevice();

    QString accept_deviceid;
    bool issuccess;
private slots:
    void post_finishedSlot(QNetworkReply *reply);
    void delete_finishedSlot(QNetworkReply *reply);
private:
    QString device_name;  //增加的时候他就是name 删除的时候是deviceid
    QNetworkAccessManager *nam;
    QNetworkReply* reply;
    static QMutex zhuce_mut;
    functionType mytype;


};
#endif // ONENET_HTTP_H
