#ifndef DATABASE_H
#define DATABASE_H
#include<QVector>

class Database
{
private:
    Database();
public:
   static Database* getDatabaseP();
    bool creat_sql_connection();
    void datatest();
    QList<unsigned char> get_lastNodes();
    bool addOneNode(unsigned char id);
    bool dropOneNode(unsigned char id);
};

#endif // DATABASE_H
