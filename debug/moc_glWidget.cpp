/****************************************************************************
** Meta object code from reading C++ file 'glWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../glWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_glWidget_t {
    QByteArrayData data[13];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_glWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_glWidget_t qt_meta_stringdata_glWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "glWidget"
QT_MOC_LITERAL(1, 9, 25), // "camera_Coordinate_Changed"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 3), // "msg"
QT_MOC_LITERAL(4, 40, 7), // "repaint"
QT_MOC_LITERAL(5, 48, 8), // "drewItem"
QT_MOC_LITERAL(6, 57, 4), // "Item"
QT_MOC_LITERAL(7, 62, 4), // "item"
QT_MOC_LITERAL(8, 67, 9), // "stopTimer"
QT_MOC_LITERAL(9, 77, 10), // "startTimer"
QT_MOC_LITERAL(10, 88, 13), // "keyPressEvent"
QT_MOC_LITERAL(11, 102, 10), // "QKeyEvent*"
QT_MOC_LITERAL(12, 113, 5) // "event"

    },
    "glWidget\0camera_Coordinate_Changed\0\0"
    "msg\0repaint\0drewItem\0Item\0item\0stopTimer\0"
    "startTimer\0keyPressEvent\0QKeyEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_glWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   47,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,
       9,    0,   52,    2, 0x0a /* Public */,
      10,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Char,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void glWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<glWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->camera_Coordinate_Changed((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 1: _t->repaint(); break;
        case 2: _t->drewItem((*reinterpret_cast< const Item(*)>(_a[1]))); break;
        case 3: _t->stopTimer(); break;
        case 4: _t->startTimer(); break;
        case 5: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (glWidget::*)(char );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&glWidget::camera_Coordinate_Changed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject glWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_glWidget.data,
    qt_meta_data_glWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *glWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *glWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_glWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions_3_3_Core"))
        return static_cast< QOpenGLFunctions_3_3_Core*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int glWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void glWidget::camera_Coordinate_Changed(char _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
