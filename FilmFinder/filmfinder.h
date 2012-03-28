#ifndef FILMFINDER_H
#define FILMFINDER_H

#include <QtGui/QMainWindow>
#include "ui_filmfinder.h"
#include <iostream>

using namespace std;

class FilmFinder : public QMainWindow
{
    Q_OBJECT

public:
    FilmFinder(QWidget *parent = 0);
    ~FilmFinder();


private slots:
    void on_yearSlider_valueChanged(int value);

    void on_actorBox_textChanged();

private:
    Ui::FilmFinderClass ui;
};

#endif // FILMFINDER_H
