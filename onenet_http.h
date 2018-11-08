#ifndef ONENET_HTTP_H
#define ONENET_HTTP_H
#include <QMainWindow>
#include<QObject>
#include <QThread>
#include<QMutex>
#include<QMutexLocker>
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
        //delete nam;
        //delete reply;
    }
    void post_data();
    void run();
    static QMutex mut;
};
class createNewDevice:public QThread
{
    Q_OBJECT
public:
    createNewDevice(QString devicename);
        void run();
        void getNewDevice();

        QString accept_deviceid;
        bool isover;
private slots:
    void post_finishedSlot(QNetworkReply *reply);
private:
    QString device_name;
    QNetworkAccessManager *nam;
    QNetworkReply* reply;

    static QMutex zhuce_mut;

};
#endif // ONENET_HTTP_H
