#ifndef FILMVIEW_H
#define FILMVIEW_H

#include <QtGui/QWidget>
#include "ui_filmview.h"
#include <iostream>

using namespace std;

class FilmView : public QWidget
{
    Q_OBJECT

public:
    FilmView(QWidget *parent = 0);
    ~FilmView();
    void populate();
    void setTitle(QString const &);
    void setYear(QString const &);
    void setTime(QString const &);
    void setActeurs(QList<QString>);
    void setDirectors(QList<QString>);

private:
    Ui::FilmViewClass ui;
};

#endif // FILMVIEW_H
