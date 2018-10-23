#ifndef _LOGIN_H
#define _LOGIN_H

#include <QWidget>
#include <QVector>
#include<QAbstractButton>
namespace Ui {
class _Login;
}
class Database;
class _Login : public QWidget
{
    Q_OBJECT
public:
    explicit _Login(QWidget *parent = 0);
    ~_Login() {delete ui;}
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
private:
    Ui::_Login *ui;
    QVector<QPair<QString,QString>> users;
    QVector<int> key = {9,4,0,3,2,8}; //秘钥
    Database *db;
};
#endif // _LOGIN_H
