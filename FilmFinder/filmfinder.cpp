#include "filmfinder.h"

FilmFinder::FilmFinder(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    searchWindow = new AdvancedSearchWindow();

    //Ou on fait un bouton pour ouvrir une nouvelle fenetre
    QPushButton *advancedSearchButton = new QPushButton(QIcon(":/images/fleche.jpg"),"", this);
    ui.layout->addWidget(advancedSearchButton);

    //Ou on fait un dock sur le coté
    QDockWidget *dock = new QDockWidget("Palette", this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock->setWidget(searchWindow);



    //Cas de la nouvelle fenetre
    connect(advancedSearchButton, SIGNAL(clicked()), this, SLOT(showAdvancedSearch()));


    connect(searchWindow->ui.actorBox,SIGNAL(textChanged()),this,SLOT(on_actorBox_textChanged()));
    connect(searchWindow->ui.yearSlider,SIGNAL(valueChanged(int)),this,SLOT(on_yearSlider_valueChanged(int)));
    connect(searchWindow->ui.yearPrecision,SIGNAL(valueChanged(int)),this,SLOT(on_yearPrecision_valueChanged(int)));
    connect(searchWindow->ui.directorBox,SIGNAL(textChanged()),this,SLOT(on_directorBox_textChanged()));
    connect(searchWindow->ui.timeSlider,SIGNAL(valueChanged(int)),this,SLOT(on_timeSlider_valueChanged(int)));
    connect(searchWindow->ui.timePrecision,SIGNAL(valueChanged(int)),this,SLOT(on_timePrecision_valueChanged(int)));

}
//TEST
FilmFinder::~FilmFinder()
{

}

void FilmFinder::showAdvancedSearch()
{
        searchWindow->show();
}
void FilmFinder::search()//On effectue notre requete de recherche (à appeler à chaque modification dans notre recherche avancée)
{
    cout<<"search"<<endl;
}

void FilmFinder::on_yearSlider_valueChanged(int value){
    this->search();
}

void FilmFinder::on_yearPrecision_valueChanged(int arg1)//Faire une recherche sur l'année (prendre en compte l'année)
{
    this->search();
}


void FilmFinder::on_timeSlider_valueChanged(int value)//Faire une recherche sur la durée (prendre en compte la précision)
{
    this->search();
}

void FilmFinder::on_timePrecision_valueChanged(int arg1)//Faire une recherche sur la durée (prendre en compte la durée)
{
    this->search();
}

void FilmFinder::on_actorBox_textChanged()//Faire une recherche sur les acteurs
{
    this->search();
}

void FilmFinder::on_directorBox_textChanged()//Faire une rechercher sur les réalisateurs
{
    this->search();
}

void FilmFinder::on_searchBtn_clicked()//Faire une recherche sur les noms (Noms dans searchBox)
{
    this->search();
}


