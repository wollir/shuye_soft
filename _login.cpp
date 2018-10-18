#include "_login.h"
#include "ui__login.h"
#include <QPushButton>
#include <QtAlgorithms>
#include <QMessageBox.h>
#include"mainwindow.h"
#include<QDebug>
#include <QFile>
#include <sstream>
#include<algorithm>

_Login::_Login(QWidget *parent) :   QWidget(parent), ui(new Ui::_Login)
{
    ui->setupUi(this);
    //设置窗体背景
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/login_background.png")));
    this->setPalette(palette);



    QString filePath =  "./user_password/login.txt";
    QFile file(filePath);
    encry = new encryption(key);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!file.atEnd()){
            QByteArray line = file.readLine();
            QString str(line);
            int len = str.size();
            auto ite = str.indexOf(' ');
            QString str1 = QString(str.begin(),ite);
            QString str2;
            if(str[len-1] != '\n')
                str2 = QString(str.begin()+ite+1);
            else
                str2 = str.mid(ite+1,len-ite-2);
            encry->Cutecode(str2);//解密
            users.push_back({str1,str2});
        }
        file.close();

    }else
        qDebug()<< "open faild";
}
void _Login::on_buttonBox_clicked(QAbstractButton *button)
{
    bool log = false;
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok)){
        QPair<QString,QString> temp;
        temp.first =  ui->LINE_user->text();//目前登录的用户信息
        temp.second = ui->LINE_password->text();
        QString str =  temp.second;
        temp.second =  str;
        for(auto X:users){
            if(X == temp){ // 存在该用户
                MainWindow *m = new MainWindow;
                m->show();
                this->hide();
                log = true;
                return;
            }
        }
        if(!log){
            QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
            ui->LINE_password->clear();
            return;
        }
    }
    this->close();
}
