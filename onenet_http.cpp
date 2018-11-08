#include "onenet_http.h"
#include<QByteArray>
#include<QUrl>
#include<QNetworkReply>
#include<QNetworkAccessManager>
#include<QMutex>
#include<QJsonObject>
#include<QJsonDocument>
const QString ZHUCE_url = "http://api.heclouds.com/devices";
const QString ZHUCE_PROTOCAL = "MQTT";
QString now;
QMutex onenetPostData::mut;
QMutex createNewDevice::zhuce_mut;
onenetPostData::onenetPostData(QString p_device_id,QString p_api_key,float p_temp,float p_humidity,float p_liquid_hight):
    device_id(p_device_id),api_key(p_api_key),temp(p_temp),humidity(p_humidity),liquid_hight(p_liquid_hight)
{

}
void onenetPostData::post_data() //推送数据上云
{
    nam = new QNetworkAccessManager;
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(post_finishedSlot(QNetworkReply*)));
    QObject::connect(this,SIGNAL(all_job_done()),this,SLOT(deleteLater())); //完了释放对象

    if(!mut.tryLock(10000)){
        qDebug() <<device_id<<"获取锁失败";
        return;
    }
    qDebug() <<device_id<<"come";
    now = device_id;
    QString url_str = "http://api.heclouds.com/devices/" + device_id+"/datapoints?type=3";
    QUrl url(url_str);
    QNetworkRequest request(url);
    QJsonObject obj;
    obj.insert("liquid_hight",QString::number(liquid_hight));
    obj.insert("temp",QString::number(temp));
    obj.insert("humidity",QString::number(humidity));
    QByteArray append = QJsonDocument(obj).toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, ("text/html; charset=utf-8"));
    request.setRawHeader(QByteArray("api-key"),api_key.toLatin1());

    nam->post(request, append);
}
void onenetPostData::run()
{
    post_data();
    exec(); //费神很
    //qDebug ()<<"当前线程id:"<<this->currentThreadId();
}
void onenetPostData::post_finishedSlot(QNetworkReply *reply)
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
//---------------------------------------------------------------------------------

createNewDevice::createNewDevice(QString devname):accept_deviceid(""),device_name(devname)
{
}

void createNewDevice::run()
{
    getNewDevice();
    exec();
}

void createNewDevice::getNewDevice()
{
    nam = new QNetworkAccessManager;
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(post_finishedSlot(QNetworkReply*)));

    if(!zhuce_mut.tryLock(5000)){
        qDebug() <<"获取注册锁失败";
        return;
    }

    QUrl url(ZHUCE_url);
    QNetworkRequest request(url);
    QJsonObject obj;
    obj.insert("title",device_name);
    obj.insert("protocol","MQTT");
    obj.insert("auth_info",device_name);
    QByteArray append = QJsonDocument(obj).toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, ("text/html; charset=utf-8"));
    request.setRawHeader(QByteArray("api-key"),QByteArray("9FAQQOyzwZp=0qAgdy3YILp80aE="));

    reply = nam->post(request, append);
    //qDebug() <<QString::fromUtf8(reply->readAll());
}

void createNewDevice::post_finishedSlot(QNetworkReply *reply)
{
    qDebug() <<"finished";
    QByteArray bytes = reply->readAll();  // bytes
    QString str = QString::fromUtf8(bytes);
    qDebug() << str;
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toLatin1(), &jsonError);
    //解析json数据
    QString res_id = "";
    if(jsonError.error == QJsonParseError::NoError)
    {
        if(jsonDoc.isObject())
        {
            QJsonObject obj = jsonDoc.object();

            if(obj.contains("data"))
            {
                QJsonValue value= obj.take("data");
                qDebug() <<value;
                QJsonObject dataObj = value.toObject();
                if(dataObj.contains("device_id")){
                     res_id =dataObj.take("device_id").toString();
                }
            }
        }
    }
    accept_deviceid =  res_id;
    isover = true;
    zhuce_mut.unlock();
    reply->deleteLater();
}
