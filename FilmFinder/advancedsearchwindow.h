#ifndef ADVANCEDSEARCHWINDOW_H
#define ADVANCEDSEARCHWINDOW_H

#include <QWidget>
#include "ui_advancedsearchwindow.h"
#include <iostream>
#include <QListWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QScriptEngine>
#include <QScriptValueIterator>

using namespace std;


class AdvancedSearchWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit AdvancedSearchWindow(QWidget *parent = 0);
    ~AdvancedSearchWindow();
    void setNumberResult(int number);

private slots:
    void on_yearSlider_valueChanged(int value);

    void on_timeSlider_valueChanged(int value);

    void slotRequestFinished(QNetworkReply *);

public:
    Ui::AdvancedSearchWindow ui;

private:
    QNetworkAccessManager *manager;
};

#endif // ADVANCEDSEARCHWINDOW_H
