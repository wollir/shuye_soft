/****************************************************************************
** Meta object code from reading C++ file 'onenet_http.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../onenet_http.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'onenet_http.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_onenetPostData_t {
    QByteArrayData data[6];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_onenetPostData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_onenetPostData_t qt_meta_stringdata_onenetPostData = {
    {
QT_MOC_LITERAL(0, 0, 14), // "onenetPostData"
QT_MOC_LITERAL(1, 15, 12), // "all_job_done"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "post_finishedSlot"
QT_MOC_LITERAL(4, 47, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 62, 5) // "reply"

    },
    "onenetPostData\0all_job_done\0\0"
    "post_finishedSlot\0QNetworkReply*\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_onenetPostData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void onenetPostData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        onenetPostData *_t = static_cast<onenetPostData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->all_job_done(); break;
        case 1: _t->post_finishedSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (onenetPostData::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&onenetPostData::all_job_done)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject onenetPostData::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_onenetPostData.data,
      qt_meta_data_onenetPostData,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *onenetPostData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *onenetPostData::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_onenetPostData.stringdata0))
        return static_cast<void*>(const_cast< onenetPostData*>(this));
    return QThread::qt_metacast(_clname);
}

int onenetPostData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void onenetPostData::all_job_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_createNewDevice_t {
    QByteArrayData data[6];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_createNewDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_createNewDevice_t qt_meta_stringdata_createNewDevice = {
    {
QT_MOC_LITERAL(0, 0, 15), // "createNewDevice"
QT_MOC_LITERAL(1, 16, 17), // "post_finishedSlot"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 50, 5), // "reply"
QT_MOC_LITERAL(5, 56, 19) // "delete_finishedSlot"

    },
    "createNewDevice\0post_finishedSlot\0\0"
    "QNetworkReply*\0reply\0delete_finishedSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_createNewDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       5,    1,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void createNewDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        createNewDevice *_t = static_cast<createNewDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->post_finishedSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->delete_finishedSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject createNewDevice::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_createNewDevice.data,
      qt_meta_data_createNewDevice,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *createNewDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *createNewDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_createNewDevice.stringdata0))
        return static_cast<void*>(const_cast< createNewDevice*>(this));
    return QThread::qt_metacast(_clname);
}

int createNewDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
