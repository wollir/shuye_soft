#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include<someapp.h>
#include<QList>
namespace Ui {
class SignIn;
}
class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = 0);
    SignIn(QList<terminal_struct> *Nodes);
    ~SignIn();
    void freshListView();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SignIn *ui;
    QList<terminal_struct> *IDs;
};

#endif // SIGNIN_H
