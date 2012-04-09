/****************************************************************************
** Meta object code from reading C++ file 'filmfinder.h'
**
** Created: Mon 9. Apr 19:13:13 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../filmfinder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filmfinder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FilmFinder[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      39,   33,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      97,   33,   11,   11, 0x08,
     129,   11,   11,   11, 0x08,
     163,  158,   11,   11, 0x08,
     198,  158,   11,   11, 0x08,
     233,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FilmFinder[] = {
    "FilmFinder\0\0showAdvancedSearch()\0value\0"
    "on_yearSlider_valueChanged(int)\0"
    "on_actorBox_textChanged()\0"
    "on_timeSlider_valueChanged(int)\0"
    "on_directorBox_textChanged()\0arg1\0"
    "on_timePrecision_valueChanged(int)\0"
    "on_yearPrecision_valueChanged(int)\0"
    "on_searchBtn_clicked()\0"
};

void FilmFinder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FilmFinder *_t = static_cast<FilmFinder *>(_o);
        switch (_id) {
        case 0: _t->showAdvancedSearch(); break;
        case 1: _t->on_yearSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_actorBox_textChanged(); break;
        case 3: _t->on_timeSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_directorBox_textChanged(); break;
        case 5: _t->on_timePrecision_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_yearPrecision_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_searchBtn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FilmFinder::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FilmFinder::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FilmFinder,
      qt_meta_data_FilmFinder, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FilmFinder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FilmFinder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FilmFinder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FilmFinder))
        return static_cast<void*>(const_cast< FilmFinder*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FilmFinder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
