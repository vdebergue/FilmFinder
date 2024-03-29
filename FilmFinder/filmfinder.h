#ifndef FILMFINDER_H
#define FILMFINDER_H

#include <QtGui/QMainWindow>
#include "ui_filmfinder.h"
#include <iostream>
#include "advancedsearchwindow.h"
#include <QDockWidget>
#include<QListWidget>
#include <QtSql/QSqlQuery>
#include "filmview.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QMovie>

#define GRID_NBRE_COL 2;

using namespace std;

class FilmFinder : public QMainWindow
{
    Q_OBJECT

public:
    FilmFinder(QWidget *parent = 0);
    ~FilmFinder();
    void search();
    void ajouterFilm(QWidget * film);
    void viderGrille();

    int year;
    int yearPrecision;
    QString actor;
    int time;
    int timePrecision;
    QString director;
    QString title;
    QString genre;


private slots:
    void showAdvancedSearch();
    void on_yearSlider_valueChanged(int value);

    void on_actorBox_textChanged();

    void on_timeSlider_valueChanged(int value);

    void on_directorBox_textChanged();

    void on_timePrecision_valueChanged(int arg1);

    void on_yearPrecision_valueChanged(int arg1);

    void on_searchBtn_clicked();

    void onEnterPressed();

    void on_clearButton_clicked();

    void on_genreComboBox_changed(QString arg1);

    void slotRequestFinished(QNetworkReply *);


private:
    Ui::FilmFinderClass ui;
    AdvancedSearchWindow *searchWindow;
    QDockWidget *dock;
    QGridLayout *gridLayout;
    int grid_ligne,grid_colonne;
    QNetworkAccessManager *manager;
};

#endif // FILMFINDER_H
