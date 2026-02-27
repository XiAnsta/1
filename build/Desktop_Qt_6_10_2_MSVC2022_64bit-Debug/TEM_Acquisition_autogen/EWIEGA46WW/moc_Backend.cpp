/****************************************************************************
** Meta object code from reading C++ file 'Backend.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Backend.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Backend.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7BackendE_t {};
} // unnamed namespace

template <> constexpr inline auto Backend::qt_create_metaobjectdata<qt_meta_tag_ZN7BackendE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Backend",
        "targetIpChanged",
        "",
        "connectionStateChanged",
        "acquisitionChanged",
        "pointChanged",
        "progressChanged",
        "monitorDataChanged",
        "waveformChanged",
        "projectChanged",
        "projectTreeChanged",
        "logMessagesChanged",
        "sendCurrentChanged",
        "sampleRateChanged",
        "stackCountChanged",
        "sampleTimeLengthChanged",
        "customParamsChanged",
        "logMessage",
        "msg",
        "isWarning",
        "appendLog",
        "onTcpStateChanged",
        "TcpClient::ConnectionState",
        "newState",
        "onTcpDataReceived",
        "data",
        "onTcpError",
        "errorMsg",
        "setSendCurrent",
        "current",
        "setSampleRate",
        "rate",
        "setStackCount",
        "count",
        "setSampleTimeLength",
        "length",
        "setCustomParams",
        "params",
        "createProjectDB",
        "fileUrl",
        "openProjectDB",
        "connectDevice",
        "disconnectDevice",
        "startAcquisition",
        "stopAcquisition",
        "skipPoint",
        "copyPreviousPointParams",
        "savePointData",
        "isQualified",
        "remark",
        "updateRecvSeries",
        "QAbstractSeries*",
        "series",
        "updateSendSeries",
        "updateOffSeries",
        "targetIp",
        "connectionState",
        "currentProjectName",
        "currentDbPath",
        "projectTreeModel",
        "QVariantList",
        "isAcquiring",
        "currentPoint",
        "progressPercent",
        "batteryVoltage",
        "internalTemp",
        "signalStrength",
        "recvWaveform",
        "sendWaveform",
        "sendCurrent",
        "sampleRate",
        "stackCount",
        "sampleTimeLength",
        "customParams",
        "logMessages"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'targetIpChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'connectionStateChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'acquisitionChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'pointChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'progressChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'monitorDataChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'waveformChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'projectChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'projectTreeChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'logMessagesChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sendCurrentChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sampleRateChanged'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stackCountChanged'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sampleTimeLengthChanged'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'customParamsChanged'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'logMessage'
        QtMocHelpers::SignalData<void(const QString &, bool)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 }, { QMetaType::Bool, 19 },
        }}),
        // Signal 'logMessage'
        QtMocHelpers::SignalData<void(const QString &)>(17, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Slot 'appendLog'
        QtMocHelpers::SlotData<void(const QString &, bool)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 }, { QMetaType::Bool, 19 },
        }}),
        // Slot 'appendLog'
        QtMocHelpers::SlotData<void(const QString &)>(20, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Slot 'onTcpStateChanged'
        QtMocHelpers::SlotData<void(TcpClient::ConnectionState)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 22, 23 },
        }}),
        // Slot 'onTcpDataReceived'
        QtMocHelpers::SlotData<void(const QByteArray &)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QByteArray, 25 },
        }}),
        // Slot 'onTcpError'
        QtMocHelpers::SlotData<void(const QString &)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Method 'setSendCurrent'
        QtMocHelpers::MethodData<void(double)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 29 },
        }}),
        // Method 'setSampleRate'
        QtMocHelpers::MethodData<void(int)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 31 },
        }}),
        // Method 'setStackCount'
        QtMocHelpers::MethodData<void(int)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 33 },
        }}),
        // Method 'setSampleTimeLength'
        QtMocHelpers::MethodData<void(int)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 35 },
        }}),
        // Method 'setCustomParams'
        QtMocHelpers::MethodData<void(const QString &)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 37 },
        }}),
        // Method 'createProjectDB'
        QtMocHelpers::MethodData<bool(const QString &)>(38, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 39 },
        }}),
        // Method 'openProjectDB'
        QtMocHelpers::MethodData<bool(const QString &)>(40, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 39 },
        }}),
        // Method 'connectDevice'
        QtMocHelpers::MethodData<void()>(41, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'disconnectDevice'
        QtMocHelpers::MethodData<void()>(42, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'startAcquisition'
        QtMocHelpers::MethodData<void()>(43, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopAcquisition'
        QtMocHelpers::MethodData<void()>(44, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'skipPoint'
        QtMocHelpers::MethodData<void()>(45, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'copyPreviousPointParams'
        QtMocHelpers::MethodData<void()>(46, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'savePointData'
        QtMocHelpers::MethodData<void(bool, const QString &)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 48 }, { QMetaType::QString, 49 },
        }}),
        // Method 'updateRecvSeries'
        QtMocHelpers::MethodData<void(QAbstractSeries *)>(50, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 51, 52 },
        }}),
        // Method 'updateSendSeries'
        QtMocHelpers::MethodData<void(QAbstractSeries *)>(53, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 51, 52 },
        }}),
        // Method 'updateOffSeries'
        QtMocHelpers::MethodData<void(QAbstractSeries *)>(54, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 51, 52 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'targetIp'
        QtMocHelpers::PropertyData<QString>(55, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'connectionState'
        QtMocHelpers::PropertyData<int>(56, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'currentProjectName'
        QtMocHelpers::PropertyData<QString>(57, QMetaType::QString, QMC::DefaultPropertyFlags, 7),
        // property 'currentDbPath'
        QtMocHelpers::PropertyData<QString>(58, QMetaType::QString, QMC::DefaultPropertyFlags, 7),
        // property 'projectTreeModel'
        QtMocHelpers::PropertyData<QVariantList>(59, 0x80000000 | 60, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 8),
        // property 'isAcquiring'
        QtMocHelpers::PropertyData<bool>(61, QMetaType::Bool, QMC::DefaultPropertyFlags, 2),
        // property 'currentPoint'
        QtMocHelpers::PropertyData<QString>(62, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'progressPercent'
        QtMocHelpers::PropertyData<int>(63, QMetaType::Int, QMC::DefaultPropertyFlags, 4),
        // property 'batteryVoltage'
        QtMocHelpers::PropertyData<double>(64, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'internalTemp'
        QtMocHelpers::PropertyData<double>(65, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'signalStrength'
        QtMocHelpers::PropertyData<double>(66, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'recvWaveform'
        QtMocHelpers::PropertyData<QVariantList>(67, 0x80000000 | 60, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 6),
        // property 'sendWaveform'
        QtMocHelpers::PropertyData<QVariantList>(68, 0x80000000 | 60, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 6),
        // property 'sendCurrent'
        QtMocHelpers::PropertyData<double>(69, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'sampleRate'
        QtMocHelpers::PropertyData<int>(70, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'stackCount'
        QtMocHelpers::PropertyData<int>(71, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'sampleTimeLength'
        QtMocHelpers::PropertyData<int>(72, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
        // property 'customParams'
        QtMocHelpers::PropertyData<QString>(73, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'logMessages'
        QtMocHelpers::PropertyData<QStringList>(74, QMetaType::QStringList, QMC::DefaultPropertyFlags, 9),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Backend, qt_meta_tag_ZN7BackendE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Backend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7BackendE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7BackendE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7BackendE_t>.metaTypes,
    nullptr
} };

void Backend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Backend *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->targetIpChanged(); break;
        case 1: _t->connectionStateChanged(); break;
        case 2: _t->acquisitionChanged(); break;
        case 3: _t->pointChanged(); break;
        case 4: _t->progressChanged(); break;
        case 5: _t->monitorDataChanged(); break;
        case 6: _t->waveformChanged(); break;
        case 7: _t->projectChanged(); break;
        case 8: _t->projectTreeChanged(); break;
        case 9: _t->logMessagesChanged(); break;
        case 10: _t->sendCurrentChanged(); break;
        case 11: _t->sampleRateChanged(); break;
        case 12: _t->stackCountChanged(); break;
        case 13: _t->sampleTimeLengthChanged(); break;
        case 14: _t->customParamsChanged(); break;
        case 15: _t->logMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 16: _t->logMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->appendLog((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 18: _t->appendLog((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->onTcpStateChanged((*reinterpret_cast<std::add_pointer_t<TcpClient::ConnectionState>>(_a[1]))); break;
        case 20: _t->onTcpDataReceived((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 21: _t->onTcpError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->setSendCurrent((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 23: _t->setSampleRate((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->setStackCount((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 25: _t->setSampleTimeLength((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 26: _t->setCustomParams((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: { bool _r = _t->createProjectDB((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 28: { bool _r = _t->openProjectDB((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->connectDevice(); break;
        case 30: _t->disconnectDevice(); break;
        case 31: _t->startAcquisition(); break;
        case 32: _t->stopAcquisition(); break;
        case 33: _t->skipPoint(); break;
        case 34: _t->copyPreviousPointParams(); break;
        case 35: _t->savePointData((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 36: _t->updateRecvSeries((*reinterpret_cast<std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 37: _t->updateSendSeries((*reinterpret_cast<std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 38: _t->updateOffSeries((*reinterpret_cast<std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 36:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 37:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 38:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::targetIpChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::connectionStateChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::acquisitionChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::pointChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::progressChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::monitorDataChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::waveformChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::projectChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::projectTreeChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::logMessagesChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::sendCurrentChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::sampleRateChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::stackCountChanged, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::sampleTimeLengthChanged, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)()>(_a, &Backend::customParamsChanged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (Backend::*)(const QString & , bool )>(_a, &Backend::logMessage, 15))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->targetIp(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->connectionState(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->currentProjectName(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->currentDbPath(); break;
        case 4: *reinterpret_cast<QVariantList*>(_v) = _t->projectTreeModel(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->isAcquiring(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->currentPoint(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->progressPercent(); break;
        case 8: *reinterpret_cast<double*>(_v) = _t->batteryVoltage(); break;
        case 9: *reinterpret_cast<double*>(_v) = _t->internalTemp(); break;
        case 10: *reinterpret_cast<double*>(_v) = _t->signalStrength(); break;
        case 11: *reinterpret_cast<QVariantList*>(_v) = _t->recvWaveform(); break;
        case 12: *reinterpret_cast<QVariantList*>(_v) = _t->sendWaveform(); break;
        case 13: *reinterpret_cast<double*>(_v) = _t->sendCurrent(); break;
        case 14: *reinterpret_cast<int*>(_v) = _t->sampleRate(); break;
        case 15: *reinterpret_cast<int*>(_v) = _t->stackCount(); break;
        case 16: *reinterpret_cast<int*>(_v) = _t->sampleTimeLength(); break;
        case 17: *reinterpret_cast<QString*>(_v) = _t->customParams(); break;
        case 18: *reinterpret_cast<QStringList*>(_v) = _t->logMessages(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTargetIp(*reinterpret_cast<QString*>(_v)); break;
        case 6: _t->setCurrentPoint(*reinterpret_cast<QString*>(_v)); break;
        case 13: _t->setSendCurrent(*reinterpret_cast<double*>(_v)); break;
        case 14: _t->setSampleRate(*reinterpret_cast<int*>(_v)); break;
        case 15: _t->setStackCount(*reinterpret_cast<int*>(_v)); break;
        case 16: _t->setSampleTimeLength(*reinterpret_cast<int*>(_v)); break;
        case 17: _t->setCustomParams(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Backend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Backend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7BackendE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Backend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Backend::targetIpChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Backend::connectionStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Backend::acquisitionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Backend::pointChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Backend::progressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Backend::monitorDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Backend::waveformChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Backend::projectChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Backend::projectTreeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Backend::logMessagesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void Backend::sendCurrentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void Backend::sampleRateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void Backend::stackCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void Backend::sampleTimeLengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void Backend::customParamsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void Backend::logMessage(const QString & _t1, bool _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1, _t2);
}
QT_WARNING_POP
