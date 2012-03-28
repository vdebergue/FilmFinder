TEMPLATE = app
TARGET = FilmFinder 

QT        += core gui 

HEADERS   += filmfinder.h \
    advancedsearchwindow.h
SOURCES   += main.cpp \
    filmfinder.cpp \
    advancedsearchwindow.cpp
FORMS     += filmfinder.ui \    
    advancedsearchwindow.ui
RESOURCES += \
    images.qrc

