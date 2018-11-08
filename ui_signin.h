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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignIn
{
public:
    QGroupBox *groupBox;
    QListView *listView;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pushButton_6;
    QSplitter *splitter_3;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QListView *listView_2;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_4;
    QSplitter *splitter_2;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;

    void setupUi(QWidget *SignIn)
    {
        if (SignIn->objectName().isEmpty())
            SignIn->setObjectName(QStringLiteral("SignIn"));
        SignIn->resize(504, 240);
        groupBox = new QGroupBox(SignIn);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(250, 10, 231, 221));
        listView = new QListView(groupBox);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(10, 20, 71, 192));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        layoutWidget_3 = new QWidget(groupBox);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(90, 70, 131, 111));
        gridLayout_3 = new QGridLayout(layoutWidget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 3, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        pushButton_5 = new QPushButton(layoutWidget_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_3->addWidget(pushButton_5, 2, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_6, 4, 0, 1, 1);

        pushButton_6 = new QPushButton(layoutWidget_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout_3->addWidget(pushButton_6, 4, 1, 1, 1);

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

        gridLayout_3->addItem(verticalSpacer_7, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 190, 54, 12));
        groupBox_2 = new QGroupBox(SignIn);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 231, 221));
        listView_2 = new QListView(groupBox_2);
        listView_2->setObjectName(QStringLiteral("listView_2"));
        listView_2->setGeometry(QRect(10, 20, 71, 192));
        listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        layoutWidget_2 = new QWidget(groupBox_2);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(90, 70, 131, 111));
        gridLayout_2 = new QGridLayout(layoutWidget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        pushButton_3 = new QPushButton(layoutWidget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 0, 1, 1);

        pushButton_4 = new QPushButton(layoutWidget_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 4, 1, 1, 1);

        splitter_2 = new QSplitter(layoutWidget_2);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(splitter_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        splitter_2->addWidget(label_4);
        lineEdit_2 = new QLineEdit(splitter_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        splitter_2->addWidget(lineEdit_2);

        gridLayout_2->addWidget(splitter_2, 0, 0, 1, 2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 190, 54, 12));

        retranslateUi(SignIn);

        QMetaObject::connectSlotsByName(SignIn);
    } // setupUi

    void retranslateUi(QWidget *SignIn)
    {
        SignIn->setWindowTitle(QApplication::translate("SignIn", "Form", 0));
        groupBox->setTitle(QApplication::translate("SignIn", "\350\277\234\347\250\213\347\273\210\347\253\257\347\256\241\347\220\206", 0));
        pushButton_5->setText(QApplication::translate("SignIn", "\346\267\273\345\212\240", 0));
        pushButton_6->setText(QApplication::translate("SignIn", "\345\210\240\351\231\244", 0));
        label_5->setText(QApplication::translate("SignIn", "\347\273\210\347\253\257\345\217\267\357\274\232", 0));
        label_3->setText(QString());
        groupBox_2->setTitle(QApplication::translate("SignIn", "\346\234\254\345\234\260\347\273\210\347\253\257\347\256\241\347\220\206", 0));
        pushButton_3->setText(QApplication::translate("SignIn", "\346\267\273\345\212\240", 0));
        pushButton_4->setText(QApplication::translate("SignIn", "\345\210\240\351\231\244", 0));
        label_4->setText(QApplication::translate("SignIn", "\347\273\210\347\253\257\345\217\267\357\274\232", 0));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SignIn: public Ui_SignIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_H
