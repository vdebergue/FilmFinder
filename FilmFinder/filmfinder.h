#ifndef FILMFINDER_H
#define FILMFINDER_H

#include <QtGui/QMainWindow>
#include "ui_filmfinder.h"

class FilmFinder : public QMainWindow
{
    Q_OBJECT

public:
    FilmFinder(QWidget *parent = 0);
    ~FilmFinder();

private:
    Ui::FilmFinderClass ui;
};

#endif // FILMFINDER_H
