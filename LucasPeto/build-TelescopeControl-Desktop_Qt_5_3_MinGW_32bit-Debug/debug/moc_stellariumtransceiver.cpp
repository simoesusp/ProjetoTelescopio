/****************************************************************************
** Meta object code from reading C++ file 'stellariumtransceiver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TelescopeControl/stellariumtransceiver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stellariumtransceiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StellariumTransceiver_t {
    QByteArrayData data[6];
    char stringdata[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StellariumTransceiver_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StellariumTransceiver_t qt_meta_stringdata_StellariumTransceiver = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 17),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 22),
QT_MOC_LITERAL(4, 64, 13),
QT_MOC_LITERAL(5, 78, 15)
    },
    "StellariumTransceiver\0slotNewConnection\0"
    "\0slotSocketDisconnected\0slotReadyRead\0"
    "slotSocketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StellariumTransceiver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StellariumTransceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StellariumTransceiver *_t = static_cast<StellariumTransceiver *>(_o);
        switch (_id) {
        case 0: _t->slotNewConnection(); break;
        case 1: _t->slotSocketDisconnected(); break;
        case 2: _t->slotReadyRead(); break;
        case 3: _t->slotSocketError(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject StellariumTransceiver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StellariumTransceiver.data,
      qt_meta_data_StellariumTransceiver,  qt_static_metacall, 0, 0}
};


const QMetaObject *StellariumTransceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StellariumTransceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StellariumTransceiver.stringdata))
        return static_cast<void*>(const_cast< StellariumTransceiver*>(this));
    return QObject::qt_metacast(_clname);
}

int StellariumTransceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE