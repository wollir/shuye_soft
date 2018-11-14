/********************************************************************************
** Form generated from reading UI file 'signin.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNIN_H
#define UI_SIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignIn
{
public:
    QTabWidget *tabWidget_2;
    QWidget *tab1;
    QWidget *layoutWidget_4;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer_8;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_5;
    QSplitter *splitter_4;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_2;
    QListView *listView_2;
    QLabel *label_2;
    QWidget *tab2;
    QLabel *label_3;
    QListView *listView_3;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_4;
    QSplitter *splitter_3;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_6;
    QLabel *label_7;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *SignIn)
    {
        if (SignIn->objectName().isEmpty())
            SignIn->setObjectName(QStringLiteral("SignIn"));
        SignIn->resize(280, 257);
        tabWidget_2 = new QTabWidget(SignIn);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(0, 0, 469, 256));
        tabWidget_2->setAcceptDrops(true);
        tabWidget_2->setAutoFillBackground(true);
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        layoutWidget_4 = new QWidget(tab1);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(90, 30, 171, 121));
        gridLayout_4 = new QGridLayout(layoutWidget_4);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_8, 4, 0, 1, 1);

        pushButton_4 = new QPushButton(layoutWidget_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_4->addWidget(pushButton_4, 4, 1, 1, 1);

        pushButton_3 = new QPushButton(layoutWidget_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_4->addWidget(pushButton_3, 2, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 2, 0, 1, 1);

        splitter_4 = new QSplitter(layoutWidget_4);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(splitter_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        splitter_4->addWidget(label_6);
        lineEdit_2 = new QLineEdit(splitter_4);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        splitter_4->addWidget(lineEdit_2);

        gridLayout_4->addWidget(splitter_4, 0, 0, 1, 2);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_9, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 5, 1, 1, 1);

        listView_2 = new QListView(tab1);
        listView_2->setObjectName(QStringLiteral("listView_2"));
        listView_2->setGeometry(QRect(10, 20, 71, 192));
        listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label_2 = new QLabel(tab1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(190, 170, 54, 12));
        tabWidget_2->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        label_3 = new QLabel(tab2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 170, 54, 12));
        listView_3 = new QListView(tab2);
        listView_3->setObjectName(QStringLiteral("listView_3"));
        listView_3->setGeometry(QRect(10, 20, 71, 192));
        listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
        layoutWidget_3 = new QWidget(tab2);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(90, 30, 179, 130));
        gridLayout_3 = new QGridLayout(layoutWidget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_5 = new QPushButton(layoutWidget_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_3->addWidget(pushButton_5, 3, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 3, 0, 1, 1);

        splitter_3 = new QSplitter(layoutWidget_3);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(splitter_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        splitter_3->addWidget(label_5);
        lineEdit_3 = new QLineEdit(splitter_3);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        splitter_3->addWidget(lineEdit_3);

        gridLayout_3->addWidget(splitter_3, 0, 0, 1, 2);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_7, 2, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_6, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 6, 1, 1, 1);

        pushButton_6 = new QPushButton(layoutWidget_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout_3->addWidget(pushButton_6, 5, 1, 1, 1);

        label_7 = new QLabel(layoutWidget_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        lineEdit_4 = new QLineEdit(layoutWidget_3);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_3->addWidget(lineEdit_4, 1, 1, 1, 1);

        tabWidget_2->addTab(tab2, QString());

        retranslateUi(SignIn);

        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SignIn);
    } // setupUi

    void retranslateUi(QWidget *SignIn)
    {
        SignIn->setWindowTitle(QApplication::translate("SignIn", "Form", 0));
        pushButton_4->setText(QApplication::translate("SignIn", "\345\210\240\351\231\244", 0));
        pushButton_3->setText(QApplication::translate("SignIn", "\346\267\273\345\212\240", 0));
        label_6->setText(QApplication::translate("SignIn", "   \347\273\210\347\253\257ID\357\274\232 ", 0));
        label_2->setText(QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab1), QApplication::translate("SignIn", "\346\234\254\345\234\260\347\273\210\347\253\257\347\256\241\347\220\206", 0));
        label_3->setText(QString());
        pushButton_5->setText(QApplication::translate("SignIn", "\346\267\273\345\212\240", 0));
        label_5->setText(QApplication::translate("SignIn", " device_id :  ", 0));
        pushButton_6->setText(QApplication::translate("SignIn", "\345\210\240\351\231\244", 0));
        label_7->setText(QApplication::translate("SignIn", " device_name :", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab2), QApplication::translate("SignIn", "\350\277\234\347\250\213\347\273\210\347\253\257\347\256\241\347\220\206", 0));
    } // retranslateUi

};

namespace Ui {
    class SignIn: public Ui_SignIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_H
