#ifndef FILMVIEW_H
#define FILMVIEW_H

#include <QtGui/QWidget>
#include "ui_filmview.h"

class FilmView : public QWidget
{
    Q_OBJECT

public:
    FilmView(QWidget *parent = 0);
    ~FilmView();
    void populate();

private:
    Ui::FilmViewClass ui;
};

#endif // FILMVIEW_H
