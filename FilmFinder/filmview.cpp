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
    ui.label_nom_film->setText("");
    ui.label_acteurs->setText("");
    ui.label_annee->setText("");
    ui.label_director->setText("");
    ui.label_duree->setText("");
    //ui.label_image->setPixmap(QPixmap("images/movie.png"));
}

void FilmView::setTitle(QString const & titre){
    ui.label_nom_film->setText("<b style='font-size:12px'>"+titre+"</b>");
    ui.label_nom_film->setAlignment(Qt::AlignCenter);
}
void FilmView::setYear(QString const & year){
    ui.label_annee->setText(year);
    ui.label_director->setAlignment(Qt::AlignCenter);
}
void FilmView::setTime(QString const & time){

    ui.label_duree->setText(time);
    ui.label_director->setAlignment(Qt::AlignCenter);
}
void FilmView::setImage(QString const & image){
    cout <<(url+image).toStdString()<<endl;
    QUrl * urlImage = new QUrl(url+image);
    ui.image_view->setUrl(*urlImage);
   // ui.label_image->setPixmap(QPixmap(url+image));
}
void FilmView::setActeurs(QList<QString> acteurs){
    QString text="";
    for(int i=0;i<acteurs.size();i++){
        text+=acteurs.at(i)+"\n";
    }
    ui.label_acteurs->setText(text);
    ui.label_director->setAlignment(Qt::AlignCenter);
}
void FilmView::setDirectors(QList<QString> directors){
    QString text="";
    for(int i=0;i<directors.size();i++){
        text+=directors.at(i)+"\n";
    }
    ui.label_director->setText(text);
    ui.label_director->setAlignment(Qt::AlignCenter);
}

void FilmView::setGenres(QList<QString> genres){
    QString text="";
    for (int i=0;i<genres.size();i++){
        text+=genres.at(i);
        cout<<i<<" "<<genres.size()-1<<endl;
        if (i!=(genres.size()-1)){
            text+=" , ";
        }
    }
    ui.label_genre->setText("<b>"+text+"</b>");
    ui.label_genre->setAlignment(Qt::AlignCenter);
}
