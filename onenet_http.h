#ifndef ONENET_HTTP_H
#define ONENET_HTTP_H
#include <QMainWindow>
#include<QObject>
#include <QThread>
#include<QMutex>
#include<QMutexLocker>
class QNetworkAccessManager;
class QNetworkReply;
class onenet_http:public QThread
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
    void finishedSlot(QNetworkReply *reply);

signals:
    void all_job_done();
public:
    onenet_http(QString p_device_id,QString p_api_key,float p_temp,float p_humidity,float p_liquid_hight);
    ~onenet_http(){
        //delete nam;
        //delete reply;
    }
    void post_data();
    void run();
    static QMutex mut;
};

#endif // ONENET_HTTP_H
