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
    ui->listView_2->setModel(model);
}
//添加节点
void SignIn::on_pushButton_3_clicked()
{
    //先看有没有
    QString str = ui->lineEdit_2->text();
    if(str.isEmpty()){
        ui->label_2->setText("Error!");
        return;
    }
    unsigned short newid = str.toInt();
    for(auto X:*IDs){
        if(X.id == newid){
            QMessageBox::warning(this,tr("警告"),tr("该节点已经存在!"),QMessageBox::Yes);
            ui->lineEdit_2->clear();
            ui->label_2->setText("Error!");
            return;
        }
    }
    terminal_struct *temp = new terminal_struct(newid);
    IDs->push_back(*temp);
    freshListView();
    //tablewidget 增加一行
    int rowIndex = tab->rowCount();
    tab->setRowCount(rowIndex + 1);//总行数增加1
    tab->setItem(rowIndex,0,new QTableWidgetItem(QString::number(newid)));
    tab->setItem(rowIndex,1,new QTableWidgetItem(QString::number(temp->liq_height,'f',1)+"mm"));
    tab->setItem(rowIndex,2,new QTableWidgetItem(QIcon(":/gray_led.png"), "离线"));
    tab->setItem(rowIndex,3,new QTableWidgetItem(temp->received_time));
    tab->setItem(rowIndex,4,new QTableWidgetItem(QString::number(temp->temprature, 10, 1)));
    tab->setItem(rowIndex,5,new QTableWidgetItem(QString::number(temp->Humidity, 10, 1)));
    //数据库中增加一行
    db->addOneNode(newid);
    ui->label_2->setText("Succeed!");
}
int find_newidNum(QList<terminal_struct> *IDs,u16 newid)
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
void SignIn::on_pushButton_4_clicked()
{
    QString str = ui->lineEdit_2->text();
    if(str.isEmpty()){
        ui->label_2->setText("Error!");
        return;
    }
    u16 newid = str.toInt();
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

void SignIn::on_listView_2_doubleClicked(const QModelIndex &index)
{
    ui->lineEdit_2->setText(index.data().toString());
}
