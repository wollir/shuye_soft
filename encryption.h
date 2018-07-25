#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include<QVector>
#include<String>
class encryption
{
public:
    explicit encryption(QVector<int> key);
    ~encryption(){}
    void Makecode(std::string &pstr);
    void Cutecode(std::string &pstr);
private:
      QVector<int> key;//加密字符
};
#endif // ENCRYPTION_H
