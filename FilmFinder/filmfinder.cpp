#include "filmfinder.h"

FilmFinder::FilmFinder(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

}
//TEST
FilmFinder::~FilmFinder()
{

}


void FilmFinder::on_yearSlider_valueChanged(int value)
{
    QString v;
    v.setNum(value);
    ui.yearValue->setText(v);
}





void FilmFinder::on_actorBox_textChanged()
{
    QString text=ui.actorBox->toPlainText();
    cout<<text.toStdString()<<endl;
}
