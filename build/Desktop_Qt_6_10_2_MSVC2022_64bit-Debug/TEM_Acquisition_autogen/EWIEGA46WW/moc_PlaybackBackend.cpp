/****************************************************************************
** Meta object code from reading C++ file 'PlaybackBackend.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../PlaybackBackend.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlaybackBackend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN15PlaybackBackendE_t {};
} // unnamed namespace

template <> constexpr inline auto PlaybackBackend::qt_create_metaobjectdata<qt_meta_tag_ZN15PlaybackBackendE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PlaybackBackend",
        "projectChanged",
        "",
        "loadedPointChanged",
        "playbackStateChanged",
        "playbackProgressChanged",
        "logMessage",
        "msg",
        "isWarning",
        "waveformChanged",
        "onPlaybackTick",
        "openPlaybackDB",
        "fileUrl",
        "getProjectTree",
        "QVariantList",
        "loadPointData",
        "pointId",
        "play",
        "pause",
        "seek",
        "progressRatio",
        "exportCsv",
        "destFolderUrl",
        "updateRecvSeries",
        "QAbstractSeries*",
        "series",
        "updateSendSeries",
        "updateOffSeries",
        "currentProjectName",
        "currentDbPath",
        "totalPoints",
        "currentPointIndex",
        "currentPointName",
        "batteryVoltage",
        "internalTemp",
        "signalStrength",
        "isPlaying",
        "playbackProgress"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'projectChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'loadedPointChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playbackStateChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playbackProgressChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'logMessage'
        QtMocHelpers::SignalData<void(const QString &, bool)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::Bool, 8 },
        }}),
        // Signal 'waveformChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onPlaybackTick'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'openPlaybackDB'
        QtMocHelpers::MethodData<bool(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 12 },
        }}),
        // Method 'getProjectTree'
        QtMocHelpers::MethodData<QVariantList()>(13, 2, QMC::AccessPublic, 0x80000000 | 14),
        // Method 'loadPointData'
        QtMocHelpers::MethodData<bool(int)>(15, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 16 },
        }}),
        // Method 'play'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'pause'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'seek'
        QtMocHelpers::MethodData<void(double)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 20 },
        }}),
        // Method 'exportCsv'
        QtMocHelpers::MethodData<void(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 22 },
        }}),
        // Method 'updateRecvSeries'
        QtMocHelpers::MethodData<void(QAbstractSeries *)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Method 'updateSendSeries'
        QtMocHelpers::MethodData<void(QAbstractSeries *)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Method 'updateOffSeries'
        QtMocHelpers::MethodData<void(QAbstractSeries *)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'currentProjectName'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'currentDbPath'
        QtMocHelpers::PropertyData<QString>(29, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'totalPoints'
        QtMocHelpers::PropertyData<int>(30, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'currentPointIndex'
        QtMocHelpers::PropertyData<int>(31, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'currentPointName'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'batteryVoltage'
        QtMocHelpers::PropertyData<double>(33, QMetaType::Double, QMC::DefaultPropertyFlags, 1),
        // property 'internalTemp'
        QtMocHelpers::PropertyData<double>(34, QMetaType::Double, QMC::DefaultPropertyFlags, 1),
        // property 'signalStrength'
        QtMocHelpers::PropertyData<double>(35, QMetaType::Double, QMC::DefaultPropertyFlags, 1),
        // property 'isPlaying'
        QtMocHelpers::PropertyData<bool>(36, QMetaType::Bool, QMC::DefaultPropertyFlags, 2),
        // property 'playbackProgress'
        QtMocHelpers::PropertyData<double>(37, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlaybackBackend, qt_meta_tag_ZN15PlaybackBackendE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PlaybackBackend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlaybackBackendE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlaybackBackendE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15PlaybackBackendE_t>.metaTypes,
    nullptr
} };

void PlaybackBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlaybackBackend *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->projectChanged(); break;
        case 1: _t->loadedPointChanged(); break;
        case 2: _t->playbackStateChanged(); break;
        case 3: _t->playbackProgressChanged(); break;
        case 4: _t->logMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 5: _t->waveformChanged(); break;
        case 6: _t->onPlaybackTick(); break;
        case 7: { bool _r = _t->openPlaybackDB((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantList _r = _t->getProjectTree();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->loadPointData((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->play(); break;
        case 11: _t->pause(); break;
        case 12: _t->seek((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 13: _t->exportCsv((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->updateRecvSeries((*reinterpret_cast<std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 15: _t->updateSendSeries((*reinterpret_cast<std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 16: _t->updateOffSeries((*reinterpret_cast<std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PlaybackBackend::*)()>(_a, &PlaybackBackend::projectChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaybackBackend::*)()>(_a, &PlaybackBackend::loadedPointChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaybackBackend::*)()>(_a, &PlaybackBackend::playbackStateChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaybackBackend::*)()>(_a, &PlaybackBackend::playbackProgressChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaybackBackend::*)(const QString & , bool )>(_a, &PlaybackBackend::logMessage, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaybackBackend::*)()>(_a, &PlaybackBackend::waveformChanged, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->currentProjectName(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->currentDbPath(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->totalPoints(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->currentPointIndex(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->currentPointName(); break;
        case 5: *reinterpret_cast<double*>(_v) = _t->batteryVoltage(); break;
        case 6: *reinterpret_cast<double*>(_v) = _t->internalTemp(); break;
        case 7: *reinterpret_cast<double*>(_v) = _t->signalStrength(); break;
        case 8: *reinterpret_cast<bool*>(_v) = _t->isPlaying(); break;
        case 9: *reinterpret_cast<double*>(_v) = _t->playbackProgress(); break;
        default: break;
        }
    }
}

const QMetaObject *PlaybackBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlaybackBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlaybackBackendE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PlaybackBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void PlaybackBackend::projectChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PlaybackBackend::loadedPointChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlaybackBackend::playbackStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PlaybackBackend::playbackProgressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PlaybackBackend::logMessage(const QString & _t1, bool _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void PlaybackBackend::waveformChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
