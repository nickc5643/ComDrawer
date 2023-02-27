/****************************************************************************
** Meta object code from reading C++ file 'ComDrawer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ComDrawer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ComDrawer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComDrawer_t {
    QByteArrayData data[12];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComDrawer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComDrawer_t qt_meta_stringdata_ComDrawer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ComDrawer"
QT_MOC_LITERAL(1, 10, 5), // "about"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 12), // "selectPencil"
QT_MOC_LITERAL(4, 30, 12), // "selectEraser"
QT_MOC_LITERAL(5, 43, 11), // "selectPaint"
QT_MOC_LITERAL(6, 55, 10), // "selectFill"
QT_MOC_LITERAL(7, 66, 18), // "selectStraightLine"
QT_MOC_LITERAL(8, 85, 8), // "setColor"
QT_MOC_LITERAL(9, 94, 8), // "setWidth"
QT_MOC_LITERAL(10, 103, 17), // "clearActiveScreen"
QT_MOC_LITERAL(11, 121, 20) // "openComicBookPreview"

    },
    "ComDrawer\0about\0\0selectPencil\0"
    "selectEraser\0selectPaint\0selectFill\0"
    "selectStraightLine\0setColor\0setWidth\0"
    "clearActiveScreen\0openComicBookPreview"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComDrawer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ComDrawer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ComDrawer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->about(); break;
        case 1: _t->selectPencil(); break;
        case 2: _t->selectEraser(); break;
        case 3: _t->selectPaint(); break;
        case 4: _t->selectFill(); break;
        case 5: _t->selectStraightLine(); break;
        case 6: _t->setColor(); break;
        case 7: _t->setWidth(); break;
        case 8: _t->clearActiveScreen(); break;
        case 9: _t->openComicBookPreview(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ComDrawer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ComDrawer.data,
    qt_meta_data_ComDrawer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ComDrawer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComDrawer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ComDrawer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ComDrawer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
