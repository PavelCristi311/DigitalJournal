/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../UILayer/MainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onAdd",
        "",
        "onUpdate",
        "onRemove",
        "onUndo",
        "onRedo",
        "onFilterAnd",
        "onFilterOr",
        "onListSelectionChanged",
        "onEntryDoubleClicked",
        "const QListWidgetItem*",
        "item",
        "onShowAll",
        "onChatbot"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onAdd'
        QtMocHelpers::SlotData<void() const>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUpdate'
        QtMocHelpers::SlotData<void() const>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRemove'
        QtMocHelpers::SlotData<void() const>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUndo'
        QtMocHelpers::SlotData<void() const>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRedo'
        QtMocHelpers::SlotData<void() const>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFilterAnd'
        QtMocHelpers::SlotData<void() const>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFilterOr'
        QtMocHelpers::SlotData<void() const>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onListSelectionChanged'
        QtMocHelpers::SlotData<void() const>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onEntryDoubleClicked'
        QtMocHelpers::SlotData<void(const QListWidgetItem *)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'onShowAll'
        QtMocHelpers::SlotData<void() const>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onChatbot'
        QtMocHelpers::SlotData<void() const>(14, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onAdd(); break;
        case 1: _t->onUpdate(); break;
        case 2: _t->onRemove(); break;
        case 3: _t->onUndo(); break;
        case 4: _t->onRedo(); break;
        case 5: _t->onFilterAnd(); break;
        case 6: _t->onFilterOr(); break;
        case 7: _t->onListSelectionChanged(); break;
        case 8: _t->onEntryDoubleClicked((*reinterpret_cast< std::add_pointer_t<const QListWidgetItem*>>(_a[1]))); break;
        case 9: _t->onShowAll(); break;
        case 10: _t->onChatbot(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
