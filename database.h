#ifndef DATABASE_H
#define DATABASE_H
#include <QList>
#include <QSqlQuery>
#include<utility>
class Database
{
private:
    Database();
    QSqlDatabase db;
public:
    bool isopen();
    static Database* getDatabaseP();
    bool creat_sql_connection();
    void datatest();
    QList<unsigned short> get_lastNodes();
    QMap<uint16_t,QString> get_online_device();
    bool DeleteFromDeviceinfo(QString id); //从device_info里删除

    bool addOneNode(unsigned short id);
    bool addto_deviceinfo(QString id,QString deviceid);
    bool dropOneNode(unsigned short id);
    bool isValidUser(QString name,QString pwd);
    QPair<QString,QString> get_device_info(uint16_t id);
    void shuye_over_action(uint16_t id); //输液完成后的操作
};

#endif // DATABASE_H
