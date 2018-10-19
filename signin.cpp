#include "signin.h"
#include "ui_signin.h"
#include<QStringListModel>
#include<QMessageBox>
SignIn::SignIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
}

SignIn::SignIn(QList<terminal_struct> *Nodes):
    QWidget(0),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    IDs = Nodes;
    freshListView();
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::freshListView()
{
    QStringList num;
    for(auto X:*IDs){
        num.push_back(QString::number(X.id));
    }
    QStringListModel *model = new QStringListModel(num);
    ui->listView->setModel(model);
}
//添加节点
void SignIn::on_pushButton_clicked()
{
    //先看有没有
    QString str = ui->lineEdit->text();
    if(str.isEmpty())
        return;
    uchar newid = str.toInt();
    for(auto X:*IDs){
        if(X.id == newid){
            QMessageBox::warning(this,tr("警告"),tr("该节点已经存在!"),QMessageBox::Yes);
            ui->lineEdit->clear();
            return;
        }
    }
    IDs->push_back( terminal_struct(newid));
    freshListView();
}
int find_newidNum(QList<terminal_struct> *IDs,uchar newid)
{
   QList<terminal_struct>::iterator ite = IDs->begin();
   int index = 0;
   for(;ite != IDs->end();++ite){
       if(ite->id == newid)
           return index;
          index ++;
   }
   return -1;
}
//删除节点
void SignIn::on_pushButton_2_clicked()
{
    QString str = ui->lineEdit->text();
    if(str.isEmpty())
        return;
     uchar newid = str.toInt();
    int index = -1;
    int count = 0;
    for(auto X:*IDs){
        if(X.id == newid){
            index = count;
            break;
        }
        count++;
    }
    if(index == -1){
        QMessageBox::warning(this,tr("警告"),tr("该节点已不存在!"),QMessageBox::Yes);
        //ui->lineEdit->clear();
        return;
    }
    IDs->removeAt(index);
    freshListView();
}
