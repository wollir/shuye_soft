#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include<QVector>
#include<String>

class QString;
class encryption
{
public:
    explicit encryption(QVector<int> key);
    ~encryption(){}
    void Makecode(QString &pstr);
    void Cutecode(QString &pstr);
private:
      QVector<int> key;//加密字符
};
#endif // ENCRYPTION_H
