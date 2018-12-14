#include "mainwindow.h"
#include <QApplication>
#include"_login.h"
#include"QDebug"
#define  NEEDLOG 0
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if !NEEDLOG
    MainWindow *m = new MainWindow;
    //m->show();
//    auto desk = a.desktop();
//    auto rect = desk.availableGeometry();
//    m->resize(rect.width()-20, rect.height()-40);
    m->showMaximized();
    qDebug() <<m->maximumSize();

#else
    _Login *log = new _Login;
    log->show();
#endif
    return a.exec();
}
