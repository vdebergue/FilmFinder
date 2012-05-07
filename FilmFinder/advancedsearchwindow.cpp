#include "advancedsearchwindow.h"
#include "ui_advancedsearchwindow.h"


AdvancedSearchWindow::AdvancedSearchWindow(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);


}

AdvancedSearchWindow::~AdvancedSearchWindow()
{

}

void AdvancedSearchWindow::on_yearSlider_valueChanged(int value)//Faire une recherche sur l'année
{
    QString v;
    v.setNum(value);
    ui.yearValue->setText(v);

}

void AdvancedSearchWindow::on_timeSlider_valueChanged(int value)//Faire une recherche sur la durée (prendre en compte la précision)
{
    QString v;
    v.setNum(value);
    ui.timeValue->setText(v);
}

void AdvancedSearchWindow::setNumberResult(int number){
    QString nombre(number);
    ui.resultNumber->setText(nombre);
}
