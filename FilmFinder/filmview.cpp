#include "filmview.h"

FilmView::FilmView(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
    populate();
}

FilmView::~FilmView()
{

}

//Fonction utilisée pour afficher les infos dans la fenetre
//TODO : a finir
void FilmView::populate(){
    ui.label_nom_film->setText("");
    ui.label_acteurs->setText("");
    ui.label_annee->setText("");
    ui.label_director->setText("");
    ui.label_duree->setText("");
	ui.label_image->setPixmap(QPixmap("images/movie.png"));
}

void FilmView::setTitle(QString const & titre){
	ui.label_nom_film->setText(titre);
}
void FilmView::setYear(QString const & year){
    ui.label_annee->setText(year);
}
void FilmView::setTime(QString const & time){

    ui.label_duree->setText(time);
}
void FilmView::setActeurs(QList<QString> acteurs){
    QString text="";
    for(int i=0;i<acteurs.size();i++){
        text+=acteurs.at(i)+" \n ";
    }
    ui.label_acteurs->setText(text);
}
void FilmView::setDirectors(QList<QString> directors){
    QString text="";
    for(int i=0;i<directors.size();i++){
        text+=directors.at(i)+" \n ";
    }
    ui.label_director->setText(text);
}
