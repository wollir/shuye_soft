#include "signin.h"
#include "ui_signin.h"
#include<QStringListModel>
#include<QMessageBox>
#include"onenet_http.h"
#include<QDebug>
#include<QTime>
QMutex create_suss;

SignIn::SignIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);

}

SignIn::SignIn(QList<terminal_struct> *Nodes,QTableWidget * tabWid,QComboBox* combox):
    QWidget(0),   ui(new Ui::SignIn),tab(tabWid)
{
    ui->setupUi(this);
     this->setWindowIcon(QIcon(":/sia.jpg"));

    db = Database::getDatabaseP();
    ui->tabWidget_2->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");;
    //ui->tabWidget_2->setParent(ui);
    IDs = Nodes;
    freshListView1();
    freshListView2();
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::freshListView1()
{
    //tab1
    QStringList num;
    for(auto X:*IDs){
        num.push_back(QString::number(X.id));
    }
    QStringListModel *model = new QStringListModel(num);
    ui->listView_2->setModel(model);
}
void SignIn::freshListView2()
{
    //tab2,需要查询数据库
    remote_id.clear();
    remote_id = db->get_online_device();
    QStringList num2strlist;
    QMap<uint16_t,QString>::iterator ite = remote_id.begin();
    for(;ite != remote_id.end();ite++){
        num2strlist.push_back(QString::number(ite.key()));
    }
    QStringListModel *model2 = new QStringListModel(num2strlist);
    ui->listView_3->setModel(model2);
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
    freshListView1();
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
    freshListView1();
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

void SignIn::on_listView_3_doubleClicked(const QModelIndex &index)
{
    ui->lineEdit_3->setText(index.data().toString());
}
//注册远程终端
void SignIn::on_pushButton_5_clicked()
{
    //增加节点
    QString id = ui->lineEdit_3->text();
    QString name = ui->lineEdit_4->text();

    if(!id.size() || !name.size() || id.toUInt() > 65535 || id.toUInt() < 1) //id name
        return;
    if(remote_id.contains(id.toUInt())){
        ui->label_3->setText("Error!");
        return ;
    }
    //远程插入
    create_suss.lock();
    createNewDevice *Cre_dev = new createNewDevice(AddNewTerm,name);
    Cre_dev->start();

//    if(create_suss.tryLock(20000)){
//        qDebug() <<"获取锁失败,未能返回device_id";
//        return;
//    }
    create_suss.tryLock(20000);
    if(Cre_dev->accept_deviceid.size() == 0){
        ui->label_3->setText("Error!");
        qDebug() <<"失败,返回空 device_id";
        create_suss.unlock();
        return;
    }
    create_suss.unlock();

    QString new_deviceid = Cre_dev->accept_deviceid;
    qDebug()<<"new_diviceid:"<<new_deviceid;


    if(!db->addto_deviceinfo(id,new_deviceid)){//插入未成功
        ;
    }
    remote_id[id.toUInt()] = new_deviceid;
    freshListView2();
    qDebug() <<"增加远程节点成功";
    ui->label_3->setText("Success!");
}
//删除节点
void SignIn::on_pushButton_6_clicked()
{

    QString id = ui->lineEdit_3->text();

    if(!remote_id.contains(id.toUInt())){
        qDebug() << "无该id";
        ui->label_3->setText("Error!");
        return ;
    }
    create_suss.lock();
    createNewDevice *Cre_dev = new createNewDevice(DeleteTerm,remote_id[id.toUInt()]);
    Cre_dev->start();

    create_suss.tryLock(20000);
    create_suss.unlock();
    if(!Cre_dev->issuccess){
        ui->label_3->setText("Error!");
        qDebug() << "删除失败";
        return;
    }
    db->DeleteFromDeviceinfo(id);
    remote_id.erase(remote_id.find(id.toUInt()));
    freshListView2();
    ui->label_3->setText("Success!");
    return;

}
