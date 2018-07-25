#include "mainwindow.h"
#include <QApplication>
#include"_login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    _Login log;
    log.show();

    return a.exec();
}
