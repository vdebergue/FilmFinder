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

//Fonction utilis�e pour afficher les infos dans la fenetre
//TODO : a finir
void FilmView::populate(){
	ui.label_nom_film->setText("Nom du film");
	ui.label_acteurs->setText("Acteurs : ");
	ui.label_annee->setText("Ann�e: ");
	ui.label_director->setText("R�alisateur: ");
	ui.label_image->setPixmap(QPixmap("images/movie.png"));
}
