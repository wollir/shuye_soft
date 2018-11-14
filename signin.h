#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include<someapp.h>
#include<QList>
#include<QComboBox>
#include"database.h"
#include<QMap>
namespace Ui {
class SignIn;
}
class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = 0);
    SignIn(QList<terminal_struct> *Nodes,QTableWidget * tabWid,QComboBox* combox);
    ~SignIn();
    void freshListView1();
    void freshListView2();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_listView_2_doubleClicked(const QModelIndex &index);

    void on_listView_3_doubleClicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::SignIn *ui;
    QList<terminal_struct> *IDs;
    QTableWidget * tab;
    Database *db;
    QMap<uint16_t,QString> remote_id;
};

#endif // SIGNIN_H
