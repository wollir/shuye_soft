/********************************************************************************
** Form generated from reading UI file '_login.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI__LOGIN_H
#define UI__LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui__Login
{
public:
    QLineEdit *LINE_user;
    QLineEdit *LINE_password;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *_Login)
    {
        if (_Login->objectName().isEmpty())
            _Login->setObjectName(QStringLiteral("_Login"));
        _Login->resize(320, 240);
        LINE_user = new QLineEdit(_Login);
        LINE_user->setObjectName(QStringLiteral("LINE_user"));
        LINE_user->setGeometry(QRect(120, 80, 113, 20));
        LINE_password = new QLineEdit(_Login);
        LINE_password->setObjectName(QStringLiteral("LINE_password"));
        LINE_password->setGeometry(QRect(120, 120, 113, 20));
        LINE_password->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        LINE_password->setEchoMode(QLineEdit::Password);
        label = new QLabel(_Login);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 80, 54, 12));
        label_2 = new QLabel(_Login);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 120, 54, 12));
        pushButton = new QPushButton(_Login);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 190, 75, 23));
        pushButton_2 = new QPushButton(_Login);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 190, 75, 23));

        retranslateUi(_Login);

        QMetaObject::connectSlotsByName(_Login);
    } // setupUi

    void retranslateUi(QWidget *_Login)
    {
        _Login->setWindowTitle(QApplication::translate("_Login", "\347\231\273\345\275\225", 0));
        label->setText(QApplication::translate("_Login", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        label_2->setText(QApplication::translate("_Login", "\345\257\206 \347\240\201\357\274\232", 0));
        pushButton->setText(QApplication::translate("_Login", "\347\231\273\345\275\225", 0));
        pushButton_2->setText(QApplication::translate("_Login", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class _Login: public Ui__Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI__LOGIN_H
