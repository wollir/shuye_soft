#include "database.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QList>
#include<QMap>
Database::Database()
{}

bool Database::isopen()
{
    return  db.open();
}
Database *Database::getDatabaseP()
{
    static Database dbase;
    return &dbase;
}
bool Database::creat_sql_connection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("shuye");
    db.setUserName("root");
    db.setPassword("456123");
    db.setPort(3306);
    bool ok = db.open(); // 尝试连接数据库
    if(ok)
        return true;//qDebug()<<"success!";
    return false;
}
void Database::datatest()
{
    QSqlQuery quety;
    quety.exec("select *from last_node");
    while(quety.next()){
        uint16_t id = quety.value(0).toInt();
        //qDebug() << id;
    }
}
QList<unsigned short> Database::get_lastNodes()
{
    QList<unsigned short> res;
    QSqlQuery quety;
    quety.exec("select *from last_node");
    while(quety.next()){
        unsigned short id = quety.value(0).toInt();
        res.push_back(id);
        //qDebug() << id;
    }
    return res;
}

QMap<uint16_t,QString> Database::get_online_device()
{
    QMap<uint16_t,QString> res;
    QSqlQuery quety;
    quety.exec("select id,device_id from device_info");
    while(quety.next()){
        unsigned short id = quety.value(0).toInt();
        QString device_id = quety.value(1).toString();
        res[id] = device_id;
        //qDebug() << id <<device_id;
    }
    return res;
}

bool Database::DeleteFromDeviceinfo(QString id)
{
    QSqlQuery quety;
    bool res =  quety.exec("DELETE FROM device_info WHERE id='"+id+"'");
    if(!res){
        qDebug() << "删除失败";
        return false;
    }
    qDebug() << "device_info 删除成功";
    return true;
}
bool Database::addto_deviceinfo(QString strID,QString deviceid)
{
    QSqlQuery quety;
    quety.exec("select * from device_info where id="+ strID);
    quety.next();
    int re = quety.value(0).toInt();
    if(re > 0){
         qDebug() <<"mysql already has";
        return false;
    }
    QString tt = "insert into device_info values(" + strID +",'"+ deviceid +"',' ')";
    qDebug() << tt;
    bool res =  quety.exec(tt);

    if(res){
        qDebug() << "插入成功";
        return true;
    }
    return false;
}
bool Database::addOneNode(unsigned short id)
{
    QSqlQuery quety;
    QString strID = QString::number(id);
    quety.exec("select count(*) from last_node where last_node='"+ strID +"'");
    quety.next();
    int re = quety.value(0).toInt();
    // qDebug() <<re;
    if(re > 0){
        return false;
    }
    bool res =  quety.exec("insert into last_node values('" + strID +"')");
    if(res)
        qDebug() << "插入成功";
}

bool Database::dropOneNode(unsigned short id)
{
    QSqlQuery quety;
    QString strID = QString::number(id);
    quety.exec("select count(*) from last_node where last_node='"+ strID +"'");
    quety.next();
    int re = quety.value(0).toInt();
    if(re < 1){
        return false;
    }
    bool res =  quety.exec("DELETE FROM last_node WHERE last_node='"+strID+"'");
    if(res)
        qDebug() << "删除成功";
    return true;
}

bool Database::isValidUser(QString name, QString pwd)
{
    QSqlQuery quety;
    quety.exec("select password from users where name=\""+name+"\"");
    quety.next();
    if( quety.value(0).toString() == pwd)
        return true;
    return false;
}
//在device_info表中获取当前id对应的device_id 和 api_key
QPair<QString, QString> Database::get_device_info(uint16_t id)
{
    QPair<QString, QString> id_api;
    QSqlQuery quety;
    quety.exec("select device_id,api_key from device_info where id=\""+QString::number(id)+"\"");
    if(quety.size() != 1)
        return {"",""};

    quety.next();
    id_api.first = quety.value(0).toString();
    id_api.second = quety.value(1).toString();
    return id_api;
}
