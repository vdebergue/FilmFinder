#include "filmfinder.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FilmFinder w;
    w.show();
    return a.exec();
}
