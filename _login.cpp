#include "_login.h"
#include "ui__login.h"
#include <QPushButton>
#include <QtAlgorithms>
#include <QMessageBox.h>
#include"mainwindow.h"
#include<QDebug>
#include <QFile>
#include <sstream>
#include"database.h"
#include <QCryptographicHash>
_Login::_Login(QWidget *parent) :   QWidget(parent), ui(new Ui::_Login)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/sia.jpg"));
    //设置窗体背景
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/login_background.png")));
    this->setPalette(palette);
    ui->LINE_user->setStyleSheet("background-color: rgb(255, 255, 255, 60);");
    ui->LINE_password->setStyleSheet("background-color: rgb(255, 255, 255, 60);");

    db = Database::getDatabaseP();
    if(!db->creat_sql_connection())
        return ;
}
//登录
void _Login::on_pushButton_clicked()
{
    QString name =  ui->LINE_user->text();//目前登录的用户信息
    QString pwd = ui->LINE_password->text();
    if(db->isValidUser(name,pwd)){ // 存在该用户
        MainWindow *m = new MainWindow(0,name);
        m->show();
        this->hide();
        return;
    }
    else{
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
        ui->LINE_password->clear();
        return;
    }
    this->close();
}

void _Login::on_pushButton_2_clicked()
{
    this->close();
}
