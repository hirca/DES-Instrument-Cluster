/****************************************************************************
** Meta object code from reading C++ file 'idashboardbridge.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../idashboardbridge.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'idashboardbridge.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS = QtMocHelpers::stringData(
    "IDashboardBridge",
    "speedChanged",
    "",
    "rpmChanged",
    "gearChanged",
    "batteryLevelChanged",
    "processCANFrame",
    "QCanBusFrame",
    "frame",
    "initialize",
    "speed",
    "rpm",
    "gear",
    "batteryLevel"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[17];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[12];
    char stringdata5[20];
    char stringdata6[16];
    char stringdata7[13];
    char stringdata8[6];
    char stringdata9[11];
    char stringdata10[6];
    char stringdata11[4];
    char stringdata12[5];
    char stringdata13[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS_t qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS = {
    {
        QT_MOC_LITERAL(0, 16),  // "IDashboardBridge"
        QT_MOC_LITERAL(17, 12),  // "speedChanged"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 10),  // "rpmChanged"
        QT_MOC_LITERAL(42, 11),  // "gearChanged"
        QT_MOC_LITERAL(54, 19),  // "batteryLevelChanged"
        QT_MOC_LITERAL(74, 15),  // "processCANFrame"
        QT_MOC_LITERAL(90, 12),  // "QCanBusFrame"
        QT_MOC_LITERAL(103, 5),  // "frame"
        QT_MOC_LITERAL(109, 10),  // "initialize"
        QT_MOC_LITERAL(120, 5),  // "speed"
        QT_MOC_LITERAL(126, 3),  // "rpm"
        QT_MOC_LITERAL(130, 4),  // "gear"
        QT_MOC_LITERAL(135, 12)   // "batteryLevel"
    },
    "IDashboardBridge",
    "speedChanged",
    "",
    "rpmChanged",
    "gearChanged",
    "batteryLevelChanged",
    "processCANFrame",
    "QCanBusFrame",
    "frame",
    "initialize",
    "speed",
    "rpm",
    "gear",
    "batteryLevel"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSIDashboardBridgeENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       4,   58, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    5 /* Public */,
       3,    0,   51,    2, 0x06,    6 /* Public */,
       4,    0,   52,    2, 0x06,    7 /* Public */,
       5,    0,   53,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   54,    2, 0x08,    9 /* Private */,
       9,    0,   57,    2, 0x08,   11 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::Int, 0x00015001, uint(0), 0,
      11, QMetaType::Int, 0x00015001, uint(1), 0,
      12, QMetaType::QString, 0x00015001, uint(2), 0,
      13, QMetaType::Int, 0x00015001, uint(3), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject IDashboardBridge::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSIDashboardBridgeENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS_t,
        // property 'speed'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'rpm'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'gear'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'batteryLevel'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<IDashboardBridge, std::true_type>,
        // method 'speedChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rpmChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gearChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'batteryLevelChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processCANFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCanBusFrame &, std::false_type>,
        // method 'initialize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void IDashboardBridge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IDashboardBridge *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->speedChanged(); break;
        case 1: _t->rpmChanged(); break;
        case 2: _t->gearChanged(); break;
        case 3: _t->batteryLevelChanged(); break;
        case 4: _t->processCANFrame((*reinterpret_cast< std::add_pointer_t<QCanBusFrame>>(_a[1]))); break;
        case 5: _t->initialize(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IDashboardBridge::*)();
            if (_t _q_method = &IDashboardBridge::speedChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IDashboardBridge::*)();
            if (_t _q_method = &IDashboardBridge::rpmChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IDashboardBridge::*)();
            if (_t _q_method = &IDashboardBridge::gearChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (IDashboardBridge::*)();
            if (_t _q_method = &IDashboardBridge::batteryLevelChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<IDashboardBridge *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->speed(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->rpm(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->gear(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->batteryLevel(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *IDashboardBridge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IDashboardBridge::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSIDashboardBridgeENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IDashboardBridge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void IDashboardBridge::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void IDashboardBridge::rpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void IDashboardBridge::gearChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void IDashboardBridge::batteryLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
