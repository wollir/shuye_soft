#-------------------------------------------------
#
# Project created by QtCreator 2017-02-25T20:53:14
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialport
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calman.cpp \
    someapp.cpp \
    _login.cpp \
    encryption.cpp

HEADERS  += mainwindow.h \
    calman.h \
    comboxfresh.h \
    someapp.h \
    gousi.h \
    _login.h \
    encryption.h

FORMS    += mainwindow.ui \
    _login.ui
LIBS += -L‚ÄùD:\Qt\Qt5.7.0\5.7\mingw53_32\lib‚Ä-lqwt
INCLUDEPATH += "D:\Qt\Qt5.7.0\5.7\mingw53_32\include\Qwt"
include (D:\Qt\Qt5.7.0\qwt-6.1.2\qwt.prf)

DISTFILES +=

RESOURCES += \
    picture.qrc
