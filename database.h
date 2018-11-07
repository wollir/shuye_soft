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
    bool addOneNode(unsigned short id);
    bool dropOneNode(unsigned short id);
    bool isValidUser(QString name,QString pwd);
    QPair<QString,QString> get_device_info(uint16_t id);
};

#endif // DATABASE_H
