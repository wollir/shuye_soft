#include "_login.h"
#include "ui__login.h"
#include <QPushButton>
#include <QtAlgorithms>
#include <QMessageBox.h>
#include"mainwindow.h"
#include<QDebug>
_Login::_Login(QWidget *parent) :   QWidget(parent), ui(new Ui::_Login)
{
    ui->setupUi(this);
    QPair<QString,QString> user;
    encry = new encryption(key);
    user.first = "wer";
    user.second = "123";
    std::string str = user.second.toStdString();
    encry->Makecode(str);
    user.second =  QString(QString::fromLocal8Bit(str.c_str()));
    users.push_back({user.first,user.second});
    //qDebug()<<user.first<<user.second;
}
void _Login::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok)){
         QPair<QString,QString> temp;
         temp.first =  ui->LINE_user->text();//目前登录的用户信息
         temp.second = ui->LINE_password->text();
         std::string str =  temp.second.toStdString();
         encry->Cutecode(str);
         temp.second =  QString(QString::fromLocal8Bit(str.c_str()));

         if(users.end() != qFind(users.begin(),users.end(),temp)){ // 存在该用户
            MainWindow *m = new MainWindow;
            m->show();
            this->hide();
            return;
        }else{
            QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
            return;
        }
    }
    this->close();
}
