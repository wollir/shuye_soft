#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include<someapp.h>
#include<QList>
#include<QComboBox>
#include"database.h"
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
    void freshListView();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_listView_2_doubleClicked(const QModelIndex &index);

private:
    Ui::SignIn *ui;
    QList<terminal_struct> *IDs;
    QTableWidget * tab;
    Database *db;
};

#endif // SIGNIN_H
