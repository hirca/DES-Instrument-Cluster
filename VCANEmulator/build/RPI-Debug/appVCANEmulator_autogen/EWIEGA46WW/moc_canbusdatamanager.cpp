/****************************************************************************
** Meta object code from reading C++ file 'canbusdatamanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../canbusdatamanager.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canbusdatamanager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS = QtMocHelpers::stringData(
    "CANBusDataManager",
    "speedCANIdChanged",
    "",
    "rpmCANIdChanged",
    "gearCANIdChanged",
    "batteryCANIdChanged",
    "isRunningChanged",
    "speedUpdateIntervalChanged",
    "rpmUpdateIntervalChanged",
    "setSpeedRange",
    "min",
    "max",
    "setSpeedProfile",
    "increasing",
    "setSpeedStepSize",
    "step",
    "setRPMRange",
    "setRPMProfile",
    "setRPMStepSize",
    "setGear",
    "gear",
    "setBatteryLevel",
    "level",
    "start",
    "stop",
    "speedCANId",
    "rpmCANId",
    "gearCANId",
    "batteryCANId",
    "isRunning",
    "speedUpdateInterval",
    "rpmUpdateInterval"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS_t {
    uint offsetsAndSizes[64];
    char stringdata0[18];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[17];
    char stringdata5[20];
    char stringdata6[17];
    char stringdata7[27];
    char stringdata8[25];
    char stringdata9[14];
    char stringdata10[4];
    char stringdata11[4];
    char stringdata12[16];
    char stringdata13[11];
    char stringdata14[17];
    char stringdata15[5];
    char stringdata16[12];
    char stringdata17[14];
    char stringdata18[15];
    char stringdata19[8];
    char stringdata20[5];
    char stringdata21[16];
    char stringdata22[6];
    char stringdata23[6];
    char stringdata24[5];
    char stringdata25[11];
    char stringdata26[9];
    char stringdata27[10];
    char stringdata28[13];
    char stringdata29[10];
    char stringdata30[20];
    char stringdata31[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS_t qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 17),  // "CANBusDataManager"
        QT_MOC_LITERAL(18, 17),  // "speedCANIdChanged"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 15),  // "rpmCANIdChanged"
        QT_MOC_LITERAL(53, 16),  // "gearCANIdChanged"
        QT_MOC_LITERAL(70, 19),  // "batteryCANIdChanged"
        QT_MOC_LITERAL(90, 16),  // "isRunningChanged"
        QT_MOC_LITERAL(107, 26),  // "speedUpdateIntervalChanged"
        QT_MOC_LITERAL(134, 24),  // "rpmUpdateIntervalChanged"
        QT_MOC_LITERAL(159, 13),  // "setSpeedRange"
        QT_MOC_LITERAL(173, 3),  // "min"
        QT_MOC_LITERAL(177, 3),  // "max"
        QT_MOC_LITERAL(181, 15),  // "setSpeedProfile"
        QT_MOC_LITERAL(197, 10),  // "increasing"
        QT_MOC_LITERAL(208, 16),  // "setSpeedStepSize"
        QT_MOC_LITERAL(225, 4),  // "step"
        QT_MOC_LITERAL(230, 11),  // "setRPMRange"
        QT_MOC_LITERAL(242, 13),  // "setRPMProfile"
        QT_MOC_LITERAL(256, 14),  // "setRPMStepSize"
        QT_MOC_LITERAL(271, 7),  // "setGear"
        QT_MOC_LITERAL(279, 4),  // "gear"
        QT_MOC_LITERAL(284, 15),  // "setBatteryLevel"
        QT_MOC_LITERAL(300, 5),  // "level"
        QT_MOC_LITERAL(306, 5),  // "start"
        QT_MOC_LITERAL(312, 4),  // "stop"
        QT_MOC_LITERAL(317, 10),  // "speedCANId"
        QT_MOC_LITERAL(328, 8),  // "rpmCANId"
        QT_MOC_LITERAL(337, 9),  // "gearCANId"
        QT_MOC_LITERAL(347, 12),  // "batteryCANId"
        QT_MOC_LITERAL(360, 9),  // "isRunning"
        QT_MOC_LITERAL(370, 19),  // "speedUpdateInterval"
        QT_MOC_LITERAL(390, 17)   // "rpmUpdateInterval"
    },
    "CANBusDataManager",
    "speedCANIdChanged",
    "",
    "rpmCANIdChanged",
    "gearCANIdChanged",
    "batteryCANIdChanged",
    "isRunningChanged",
    "speedUpdateIntervalChanged",
    "rpmUpdateIntervalChanged",
    "setSpeedRange",
    "min",
    "max",
    "setSpeedProfile",
    "increasing",
    "setSpeedStepSize",
    "step",
    "setRPMRange",
    "setRPMProfile",
    "setRPMStepSize",
    "setGear",
    "gear",
    "setBatteryLevel",
    "level",
    "start",
    "stop",
    "speedCANId",
    "rpmCANId",
    "gearCANId",
    "batteryCANId",
    "isRunning",
    "speedUpdateInterval",
    "rpmUpdateInterval"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCANBusDataManagerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       7,  153, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  116,    2, 0x06,    8 /* Public */,
       3,    0,  117,    2, 0x06,    9 /* Public */,
       4,    0,  118,    2, 0x06,   10 /* Public */,
       5,    0,  119,    2, 0x06,   11 /* Public */,
       6,    0,  120,    2, 0x06,   12 /* Public */,
       7,    0,  121,    2, 0x06,   13 /* Public */,
       8,    0,  122,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    2,  123,    2, 0x0a,   15 /* Public */,
      12,    1,  128,    2, 0x0a,   18 /* Public */,
      14,    1,  131,    2, 0x0a,   20 /* Public */,
      16,    2,  134,    2, 0x0a,   22 /* Public */,
      17,    1,  139,    2, 0x0a,   25 /* Public */,
      18,    1,  142,    2, 0x0a,   27 /* Public */,
      19,    1,  145,    2, 0x0a,   29 /* Public */,
      21,    1,  148,    2, 0x0a,   31 /* Public */,
      23,    0,  151,    2, 0x0a,   33 /* Public */,
      24,    0,  152,    2, 0x0a,   34 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      25, QMetaType::QString, 0x00015103, uint(0), 0,
      26, QMetaType::QString, 0x00015103, uint(1), 0,
      27, QMetaType::QString, 0x00015103, uint(2), 0,
      28, QMetaType::QString, 0x00015103, uint(3), 0,
      29, QMetaType::Bool, 0x00015001, uint(4), 0,
      30, QMetaType::Int, 0x00015103, uint(5), 0,
      31, QMetaType::Int, 0x00015103, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject CANBusDataManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCANBusDataManagerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS_t,
        // property 'speedCANId'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'rpmCANId'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'gearCANId'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'batteryCANId'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'isRunning'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'speedUpdateInterval'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'rpmUpdateInterval'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CANBusDataManager, std::true_type>,
        // method 'speedCANIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rpmCANIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gearCANIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'batteryCANIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'isRunningChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'speedUpdateIntervalChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rpmUpdateIntervalChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setSpeedRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setSpeedProfile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSpeedStepSize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setRPMRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setRPMProfile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setRPMStepSize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setGear'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setBatteryLevel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CANBusDataManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CANBusDataManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->speedCANIdChanged(); break;
        case 1: _t->rpmCANIdChanged(); break;
        case 2: _t->gearCANIdChanged(); break;
        case 3: _t->batteryCANIdChanged(); break;
        case 4: _t->isRunningChanged(); break;
        case 5: _t->speedUpdateIntervalChanged(); break;
        case 6: _t->rpmUpdateIntervalChanged(); break;
        case 7: _t->setSpeedRange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->setSpeedProfile((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->setSpeedStepSize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->setRPMRange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->setRPMProfile((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->setRPMStepSize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->setGear((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->setBatteryLevel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->start(); break;
        case 16: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CANBusDataManager::*)();
            if (_t _q_method = &CANBusDataManager::speedCANIdChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CANBusDataManager::*)();
            if (_t _q_method = &CANBusDataManager::rpmCANIdChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CANBusDataManager::*)();
            if (_t _q_method = &CANBusDataManager::gearCANIdChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CANBusDataManager::*)();
            if (_t _q_method = &CANBusDataManager::batteryCANIdChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CANBusDataManager::*)();
            if (_t _q_method = &CANBusDataManager::isRunningChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CANBusDataManager::*)();
            if (_t _q_method = &CANBusDataManager::speedUpdateIntervalChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CANBusDataManager::*)();
            if (_t _q_method = &CANBusDataManager::rpmUpdateIntervalChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CANBusDataManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->speedCANId(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->rpmCANId(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->gearCANId(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->batteryCANId(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->isRunning(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->speedUpdateInterval(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->rpmUpdateInterval(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CANBusDataManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSpeedCANId(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setRpmCANId(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setGearCANId(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setBatteryCANId(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setSpeedUpdateInterval(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setRpmUpdateInterval(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *CANBusDataManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CANBusDataManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCANBusDataManagerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CANBusDataManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CANBusDataManager::speedCANIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CANBusDataManager::rpmCANIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CANBusDataManager::gearCANIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CANBusDataManager::batteryCANIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CANBusDataManager::isRunningChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CANBusDataManager::speedUpdateIntervalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CANBusDataManager::rpmUpdateIntervalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
