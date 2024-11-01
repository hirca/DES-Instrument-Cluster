/****************************************************************************
** Meta object code from reading C++ file 'canreader.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../canreader.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canreader.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSCANReaderENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCANReaderENDCLASS = QtMocHelpers::stringData(
    "CANReader",
    "rpmChanged",
    "",
    "speedChanged",
    "gearStateChanged",
    "processReceivedFrames",
    "updateRPM",
    "rpm",
    "speed",
    "gearState"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCANReaderENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[10];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[17];
    char stringdata5[22];
    char stringdata6[10];
    char stringdata7[4];
    char stringdata8[6];
    char stringdata9[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCANReaderENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCANReaderENDCLASS_t qt_meta_stringdata_CLASSCANReaderENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "CANReader"
        QT_MOC_LITERAL(10, 10),  // "rpmChanged"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 12),  // "speedChanged"
        QT_MOC_LITERAL(35, 16),  // "gearStateChanged"
        QT_MOC_LITERAL(52, 21),  // "processReceivedFrames"
        QT_MOC_LITERAL(74, 9),  // "updateRPM"
        QT_MOC_LITERAL(84, 3),  // "rpm"
        QT_MOC_LITERAL(88, 5),  // "speed"
        QT_MOC_LITERAL(94, 9)   // "gearState"
    },
    "CANReader",
    "rpmChanged",
    "",
    "speedChanged",
    "gearStateChanged",
    "processReceivedFrames",
    "updateRPM",
    "rpm",
    "speed",
    "gearState"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCANReaderENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       3,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    4 /* Public */,
       3,    0,   45,    2, 0x06,    5 /* Public */,
       4,    0,   46,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   47,    2, 0x08,    7 /* Private */,
       6,    0,   48,    2, 0x08,    8 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::Int, 0x00015001, uint(0), 0,
       8, QMetaType::Double, 0x00015001, uint(1), 0,
       9, QMetaType::QString, 0x00015001, uint(2), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject CANReader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSCANReaderENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCANReaderENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCANReaderENDCLASS_t,
        // property 'rpm'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'speed'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'gearState'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CANReader, std::true_type>,
        // method 'rpmChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'speedChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gearStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processReceivedFrames'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateRPM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CANReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CANReader *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rpmChanged(); break;
        case 1: _t->speedChanged(); break;
        case 2: _t->gearStateChanged(); break;
        case 3: _t->processReceivedFrames(); break;
        case 4: _t->updateRPM(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CANReader::*)();
            if (_t _q_method = &CANReader::rpmChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CANReader::*)();
            if (_t _q_method = &CANReader::speedChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CANReader::*)();
            if (_t _q_method = &CANReader::gearStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CANReader *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->rpm(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->speed(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->gearState(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *CANReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CANReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCANReaderENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CANReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CANReader::rpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CANReader::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CANReader::gearStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
