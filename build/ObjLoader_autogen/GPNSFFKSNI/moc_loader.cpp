/****************************************************************************
** Meta object code from reading C++ file 'loader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../obj_viewer/viewer/loader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_objv__Loader_t {
    QByteArrayData data[11];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_objv__Loader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_objv__Loader_t qt_meta_stringdata_objv__Loader = {
    {
QT_MOC_LITERAL(0, 0, 12), // "objv::Loader"
QT_MOC_LITERAL(1, 13, 5), // "Scale"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "SetEdgeSize"
QT_MOC_LITERAL(4, 32, 13), // "SetVertexSize"
QT_MOC_LITERAL(5, 46, 11), // "SetViewType"
QT_MOC_LITERAL(6, 58, 13), // "SetVertexType"
QT_MOC_LITERAL(7, 72, 11), // "SetEdgeType"
QT_MOC_LITERAL(8, 84, 17), // "SetProjectionType"
QT_MOC_LITERAL(9, 102, 14), // "SetShadingType"
QT_MOC_LITERAL(10, 117, 11) // "UpdateFrame"

    },
    "objv::Loader\0Scale\0\0SetEdgeSize\0"
    "SetVertexSize\0SetViewType\0SetVertexType\0"
    "SetEdgeType\0SetProjectionType\0"
    "SetShadingType\0UpdateFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_objv__Loader[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       3,    1,   62,    2, 0x0a /* Public */,
       4,    1,   65,    2, 0x0a /* Public */,
       5,    1,   68,    2, 0x0a /* Public */,
       6,    1,   71,    2, 0x0a /* Public */,
       7,    1,   74,    2, 0x0a /* Public */,
       8,    1,   77,    2, 0x0a /* Public */,
       9,    1,   80,    2, 0x0a /* Public */,
      10,    0,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void objv::Loader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Loader *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Scale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->SetEdgeSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SetVertexSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SetViewType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetVertexType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SetEdgeType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->SetProjectionType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->SetShadingType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->UpdateFrame(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject objv::Loader::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_objv__Loader.data,
    qt_meta_data_objv__Loader,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *objv::Loader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *objv::Loader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_objv__Loader.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int objv::Loader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
