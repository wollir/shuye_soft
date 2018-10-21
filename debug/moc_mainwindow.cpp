/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[399];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "add_com"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "serialRead"
QT_MOC_LITERAL(4, 31, 8), // "timeout_"
QT_MOC_LITERAL(5, 40, 32), // "on_comboBox_2_currentTextChanged"
QT_MOC_LITERAL(6, 73, 4), // "arg1"
QT_MOC_LITERAL(7, 78, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(8, 102, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(9, 124, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(10, 148, 24), // "on_clear_receive_clicked"
QT_MOC_LITERAL(11, 173, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(12, 197, 17), // "call_for_terminal"
QT_MOC_LITERAL(13, 215, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(14, 239, 20), // "on_refresh_b_clicked"
QT_MOC_LITERAL(15, 260, 32), // "on_comboBox_3_currentTextChanged"
QT_MOC_LITERAL(16, 293, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(17, 325, 5), // "index"
QT_MOC_LITERAL(18, 331, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(19, 355, 32), // "on_tableWidget_cellDoubleClicked"
QT_MOC_LITERAL(20, 388, 3), // "row"
QT_MOC_LITERAL(21, 392, 6) // "column"

    },
    "MainWindow\0add_com\0\0serialRead\0timeout_\0"
    "on_comboBox_2_currentTextChanged\0arg1\0"
    "on_pushButton_3_clicked\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked\0"
    "on_clear_receive_clicked\0"
    "on_pushButton_4_clicked\0call_for_terminal\0"
    "on_pushButton_5_clicked\0on_refresh_b_clicked\0"
    "on_comboBox_3_currentTextChanged\0"
    "on_comboBox_currentIndexChanged\0index\0"
    "on_pushButton_6_clicked\0"
    "on_tableWidget_cellDoubleClicked\0row\0"
    "column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    1,   97,    2, 0x08 /* Private */,
       7,    0,  100,    2, 0x08 /* Private */,
       8,    0,  101,    2, 0x08 /* Private */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,
      15,    1,  108,    2, 0x08 /* Private */,
      16,    1,  111,    2, 0x08 /* Private */,
      18,    0,  114,    2, 0x08 /* Private */,
      19,    2,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->add_com(); break;
        case 1: _t->serialRead(); break;
        case 2: _t->timeout_(); break;
        case 3: _t->on_comboBox_2_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_3_clicked(); break;
        case 5: _t->on_pushButton_clicked(); break;
        case 6: _t->on_pushButton_2_clicked(); break;
        case 7: _t->on_clear_receive_clicked(); break;
        case 8: _t->on_pushButton_4_clicked(); break;
        case 9: _t->call_for_terminal(); break;
        case 10: _t->on_pushButton_5_clicked(); break;
        case 11: _t->on_refresh_b_clicked(); break;
        case 12: _t->on_comboBox_3_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_pushButton_6_clicked(); break;
        case 15: _t->on_tableWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::add_com)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::add_com()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
