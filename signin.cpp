#include "signin.h"
#include "ui_signin.h"
#include<QStringListModel>
#include<QMessageBox>
SignIn::SignIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    db = Database::getDatabaseP();
}

SignIn::SignIn(QList<terminal_struct> *Nodes,QTableWidget * tabWid,QComboBox* combox):
    QWidget(0),   ui(new Ui::SignIn),tab(tabWid)
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
    if(str.isEmpty()){
        ui->label_2->setText("Error!");
        return;
    }
    uchar newid = str.toInt();
    for(auto X:*IDs){
        if(X.id == newid){
            QMessageBox::warning(this,tr("警告"),tr("该节点已经存在!"),QMessageBox::Yes);
            ui->lineEdit->clear();
            ui->label_2->setText("Error!");
            return;
        }
    }
    IDs->push_back(terminal_struct(newid));
    freshListView();
    //tablewidget 增加一行
    int rowIndex = tab->rowCount();
    tab->setRowCount(rowIndex + 1);//总行数增加1
    tab->setItem(rowIndex,0,new QTableWidgetItem(QString::number(newid)));
    //数据库中增加一行
    db->addOneNode(newid);
    ui->label_2->setText("Succeed!");
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
    if(str.isEmpty()){
        ui->label_2->setText("Error!");
        return;
    }
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
        ui->label_2->setText("Error!");
        return;
    }
    IDs->removeAt(index);
    freshListView();
    int hang = LineInTableWidget(tab,newid);
    tab->removeRow(hang);
    //数据库中last_node中删除
    db->dropOneNode(newid);
    ui->label_2->setText("Succeed!");
}

void SignIn::on_listView_doubleClicked(const QModelIndex &index)
{
    ui->lineEdit->setText(index.data().toString());
}
