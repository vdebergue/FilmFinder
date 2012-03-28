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

void AdvancedSearchWindow::on_yearPrecision_valueChanged(int arg1)//Faire une recherche sur l'année (prendre en compte l'année)
{

}


void AdvancedSearchWindow::on_timeSlider_valueChanged(int value)//Faire une recherche sur la durée (prendre en compte la précision)
{
    QString v;
    v.setNum(value);
    ui.timeValue->setText(v);
}

void AdvancedSearchWindow::on_timePrecision_valueChanged(int arg1)//Faire une recherche sur la durée (prendre en compte la durée)
{

}

void AdvancedSearchWindow::on_actorBox_textChanged()//Faire une recherche sur les acteurs
{
    QString text=ui.actorBox->toPlainText();
    cout<<text.toStdString()<<endl;
}

void AdvancedSearchWindow::on_directorBox_textChanged()//Faire une rechercher sur les réalisateurs
{

}
