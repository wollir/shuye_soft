#-------------------------------------------------
#
# Project created by QtCreator 2017-02-25T20:53:14
#
#-------------------------------------------------

QT       += core gui network
QT       += serialport
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialport
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    calman.cpp \
    someapp.cpp \
    _login.cpp \
    signin.cpp \
    database.cpp \
    onenet_http.cpp

HEADERS  += mainwindow.h \
    calman.h \
    comboxfresh.h \
    someapp.h \
    gousi.h \
    _login.h \
    signin.h \
    database.h \
    onenet_http.h

FORMS    += mainwindow.ui \
    _login.ui \
    signin.ui
LIBS += -L”D:\Qt\Qt5.7.0\5.7\mingw53_32\lib�-lqwt
INCLUDEPATH += "D:\Qt\Qt5.7.0\5.7\mingw53_32\include\Qwt"
include (D:\Qt\Qt5.7.0\qwt-6.1.2\qwt.prf)

DISTFILES += \
    alarm.gif \
    gray_led.png

RESOURCES += \
    picture.qrc
