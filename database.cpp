#include "database.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QList>

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
        uchar id = quety.value(0).toInt();
        qDebug() << id;
    }
}
QList<unsigned char> Database::get_lastNodes()
{
    QList<unsigned char> res;
    QSqlQuery quety;
    quety.exec("select *from last_node");
    while(quety.next()){
        uchar id = quety.value(0).toInt();
        res.push_back(id);
        qDebug() << id;
    }
    return res;
}

bool Database::addOneNode(unsigned char id)
{
    QSqlQuery quety;
    QString strID = QString::number(id);
    quety.exec("select count(*) from last_node where last_node='"+ strID +"'");
    quety.next();
    int re = quety.value(0).toInt();
    qDebug() <<re;
    if(re > 0){
        return false;
    }
    bool res =  quety.exec("insert into last_node values('" + strID +"')");
    if(res)
        qDebug() << "插入成功";
}

bool Database::dropOneNode(unsigned char id)
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
