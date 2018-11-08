#include "onenet_http.h"
#include<QByteArray>
#include<QUrl>
#include<QNetworkReply>
#include<QNetworkAccessManager>
#include<QMutex>

QString now;
QMutex onenet_http::mut;
onenet_http::onenet_http(QString p_device_id,QString p_api_key,float p_temp,float p_humidity,float p_liquid_hight):
    device_id(p_device_id),api_key(p_api_key),temp(p_temp),humidity(p_humidity),liquid_hight(p_liquid_hight)
{}

void onenet_http::post_data()
{

    if(!mut.tryLock(10000)){
        qDebug() <<device_id<<"获取锁失败";
        return;
    }
    qDebug() <<device_id<<"come";
    now = device_id;
    QString url_str = "http://api.heclouds.com/devices/" + device_id+"/datapoints?type=3";
    QUrl url(url_str);
    QNetworkRequest request(url);
    QByteArray append;
    append.append("{\"liquid_hight\":"+QString::number(liquid_hight)+",\"temp\":"+QString::number(temp)+",\"humidity\":"+QString::number(humidity)+"}");
    request.setHeader(QNetworkRequest::ContentTypeHeader, ("text/html; charset=utf-8"));
    request.setRawHeader(QByteArray("api-key"),api_key.toLatin1());

    nam->post(request, append);
}


void onenet_http::run()
{
    nam = new QNetworkAccessManager;
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)));
    QObject::connect(this,SIGNAL(all_job_done()),this,SLOT(deleteLater())); //完了释放对象
    post_data();
    exec(); //费神很
    //qDebug ()<<"当前线程id:"<<this->currentThreadId();
}
void onenet_http::finishedSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError){
        QByteArray bytes = reply->readAll();  // bytes
        //QString string(bytes); // string
        QString string = QString::fromUtf8(bytes);
        qDebug() << string;
    }
    qDebug() <<now<<"gone!";
    mut.unlock();
    this->exit(0);
    while(this->isRunning())
        ;
    emit all_job_done();
}
