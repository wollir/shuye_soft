#include "mainwindow.h"
#include <QApplication>
#include"_login.h"

//#define  NEEDLOG
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifndef NEEDLOG
    MainWindow *m = new MainWindow;
    m->show();
#else
    _Login *log = new _Login;
    log->show();
#endif
    return a.exec();
}
