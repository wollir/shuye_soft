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
    db = Database::getDatabaseP();
    if(!db->creat_sql_connection())
        return ;
}
void _Login::on_buttonBox_clicked(QAbstractButton *button)
{
    bool log = false;
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok)){
        QString name =  ui->LINE_user->text();//目前登录的用户信息
        QString pwd = ui->LINE_password->text();
        if(db->isValidUser(name,pwd)){ // 存在该用户
            MainWindow *m = new MainWindow;
            m->show();
            this->hide();
            log = true;
            return;
        }
        if(!log){
            QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
            ui->LINE_password->clear();
            return;
        }
    }
    this->close();
}
