#ifndef ADVANCEDSEARCHWINDOW_H
#define ADVANCEDSEARCHWINDOW_H

#include <QWidget>
#include "ui_advancedsearchwindow.h"
#include <iostream>
#include <QListWidget>

using namespace std;




class AdvancedSearchWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit AdvancedSearchWindow(QWidget *parent = 0);
    ~AdvancedSearchWindow();

private slots:
    void on_yearSlider_valueChanged(int value);

    void on_actorBox_textChanged();

    void on_timeSlider_valueChanged(int value);

    void on_directorBox_textChanged();

    void on_timePrecision_valueChanged(int arg1);

    void on_yearPrecision_valueChanged(int arg1);

    
public:
    Ui::AdvancedSearchWindow ui;
};

#endif // ADVANCEDSEARCHWINDOW_H
