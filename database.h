#ifndef DATABASE_H
#define DATABASE_H
#include <QList>
#include <QSqlQuery>

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
    QList<unsigned char> get_lastNodes();
    bool addOneNode(unsigned char id);
    bool dropOneNode(unsigned char id);
    bool isValidUser(QString name,QString pwd);
};

#endif // DATABASE_H
