TEMPLATE = app
TARGET = FilmFinder
QT += core \
    gui \
    network
HEADERS += filmview.h \
    advancedsearchwindow.h \
    filmfinder.h
SOURCES += filmview.cpp \
    advancedsearchwindow.cpp \
    main.cpp \
    filmfinder.cpp
FORMS += filmview.ui \
    advancedsearchwindow.ui \
    filmfinder.ui
RESOURCES += images.qrc

