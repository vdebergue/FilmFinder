#ifndef FILMVIEW_H
#define FILMVIEW_H

#include <QtGui/QWidget>
#include "ui_filmview.h"
#include <iostream>
#include <QUrl>
#include <QtWebKit/QWebView>

using namespace std;

 const QString url ="http://perso.telecom-paristech.fr/~oudet/filmfinder/images/";

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
    void setImage(QString const &);
    void setActeurs(QList<QString>);
    void setDirectors(QList<QString>);



private:
    Ui::FilmViewClass ui;
};

#endif // FILMVIEW_H
