/****************************************************************************
** Meta object code from reading C++ file 'finestraprincipale.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FreedomElectra/finestraprincipale.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'finestraprincipale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FinestraPrincipale_t {
    QByteArrayData data[5];
    char stringdata[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FinestraPrincipale_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FinestraPrincipale_t qt_meta_stringdata_FinestraPrincipale = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 28),
QT_MOC_LITERAL(2, 48, 0),
QT_MOC_LITERAL(3, 49, 24),
QT_MOC_LITERAL(4, 74, 4)
    },
    "FinestraPrincipale\0apriFinestraInserisciCliente\0"
    "\0apriFinestraCercaCliente\0esci"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FinestraPrincipale[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FinestraPrincipale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FinestraPrincipale *_t = static_cast<FinestraPrincipale *>(_o);
        switch (_id) {
        case 0: _t->apriFinestraInserisciCliente(); break;
        case 1: _t->apriFinestraCercaCliente(); break;
        case 2: _t->esci(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FinestraPrincipale::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FinestraPrincipale.data,
      qt_meta_data_FinestraPrincipale,  qt_static_metacall, 0, 0}
};


const QMetaObject *FinestraPrincipale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FinestraPrincipale::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FinestraPrincipale.stringdata))
        return static_cast<void*>(const_cast< FinestraPrincipale*>(this));
    return QDialog::qt_metacast(_clname);
}

int FinestraPrincipale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
