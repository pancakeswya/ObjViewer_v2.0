/****************************************************************************
** Meta object code from reading C++ file 'viewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../objviewer/viewer/viewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_objv__Viewer_t {
    QByteArrayData data[13];
    char stringdata0[336];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_objv__Viewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_objv__Viewer_t qt_meta_stringdata_objv__Viewer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "objv::Viewer"
QT_MOC_LITERAL(1, 13, 36), // "OnDoubleSpinBoxStepScaleValue..."
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 35), // "OnDoubleSpinBoxStepMoveValueC..."
QT_MOC_LITERAL(4, 87, 27), // "OnPushButtonOpenFileClicked"
QT_MOC_LITERAL(5, 115, 26), // "OnPushButtonBgColorClicked"
QT_MOC_LITERAL(6, 142, 28), // "OnPushButtonEdgeColorClicked"
QT_MOC_LITERAL(7, 171, 30), // "OnPushButtonVertexColorClicked"
QT_MOC_LITERAL(8, 202, 31), // "OnDoubleSpinBoxMoveValueChanged"
QT_MOC_LITERAL(9, 234, 27), // "OnSpinBoxRotateValueChanged"
QT_MOC_LITERAL(10, 262, 25), // "OnPushButtonScreenClicked"
QT_MOC_LITERAL(11, 288, 24), // "OnPushButtonResetClicked"
QT_MOC_LITERAL(12, 313, 22) // "OnPushButtonGifClicked"

    },
    "objv::Viewer\0OnDoubleSpinBoxStepScaleValueChanged\0"
    "\0OnDoubleSpinBoxStepMoveValueChanged\0"
    "OnPushButtonOpenFileClicked\0"
    "OnPushButtonBgColorClicked\0"
    "OnPushButtonEdgeColorClicked\0"
    "OnPushButtonVertexColorClicked\0"
    "OnDoubleSpinBoxMoveValueChanged\0"
    "OnSpinBoxRotateValueChanged\0"
    "OnPushButtonScreenClicked\0"
    "OnPushButtonResetClicked\0"
    "OnPushButtonGifClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_objv__Viewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       3,    1,   72,    2, 0x08 /* Private */,
       4,    0,   75,    2, 0x08 /* Private */,
       5,    0,   76,    2, 0x08 /* Private */,
       6,    0,   77,    2, 0x08 /* Private */,
       7,    0,   78,    2, 0x08 /* Private */,
       8,    1,   79,    2, 0x08 /* Private */,
       9,    1,   82,    2, 0x08 /* Private */,
      10,    0,   85,    2, 0x08 /* Private */,
      11,    0,   86,    2, 0x08 /* Private */,
      12,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void objv::Viewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Viewer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnDoubleSpinBoxStepScaleValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->OnDoubleSpinBoxStepMoveValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->OnPushButtonOpenFileClicked(); break;
        case 3: _t->OnPushButtonBgColorClicked(); break;
        case 4: _t->OnPushButtonEdgeColorClicked(); break;
        case 5: _t->OnPushButtonVertexColorClicked(); break;
        case 6: _t->OnDoubleSpinBoxMoveValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->OnSpinBoxRotateValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->OnPushButtonScreenClicked(); break;
        case 9: _t->OnPushButtonResetClicked(); break;
        case 10: _t->OnPushButtonGifClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject objv::Viewer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_objv__Viewer.data,
    qt_meta_data_objv__Viewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *objv::Viewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *objv::Viewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_objv__Viewer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int objv::Viewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
