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
    ui.label_annee->setText("Année: ");
    ui.label_annee->setText(year);
}
void FilmView::setTime(QString const & time){
    ui.label_duree->setText("Durée: ");
    ui.label_duree->setText(time);
}
/*void FilmView::setActeurs(QList<QString> acteurs){
    ui.label_acteurs->setText("Acteurs : ");
    for(int i=0;i<acteurs.size();i++){
        ui.label_acteurs->setText(acteurs.at(i));
    }
}*/
