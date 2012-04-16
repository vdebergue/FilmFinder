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

#define GRID_NBRE_COL 3;

using namespace std;

class FilmFinder : public QMainWindow
{
    Q_OBJECT

public:
    FilmFinder(QWidget *parent = 0);
    ~FilmFinder();
    void search();
    void ajouterFilm(QWidget * film);


private slots:
    void showAdvancedSearch();
    void on_yearSlider_valueChanged(int value);

    void on_actorBox_textChanged();

    void on_timeSlider_valueChanged(int value);

    void on_directorBox_textChanged();

    void on_timePrecision_valueChanged(int arg1);

    void on_yearPrecision_valueChanged(int arg1);

    void on_searchBtn_clicked();


private:
    Ui::FilmFinderClass ui;
    AdvancedSearchWindow *searchWindow;
    QDockWidget *dock;
    QGridLayout *gridLayout;
    int grid_ligne,grid_colonne;
};

#endif // FILMFINDER_H
