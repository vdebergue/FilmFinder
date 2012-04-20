#include "filmfinder.h"

FilmFinder::FilmFinder(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    searchWindow = new AdvancedSearchWindow();

    //Ou on fait un bouton pour ouvrir une nouvelle fenetre
    QPushButton *advancedSearchButton = new QPushButton(QIcon(":/images/fleche.png"),"", this);
    ui.layout->addWidget(advancedSearchButton);

    //Ou on fait un dock sur le cot�
    dock = new QDockWidget("Advanced Search", this);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setMinimumWidth(250);
    dock->setMaximumSize(250,400);
    dock->setWidget(searchWindow);
    dock->hide();


    //Cas de la nouvelle fenetre
    connect(advancedSearchButton, SIGNAL(clicked()), this, SLOT(showAdvancedSearch()));


    connect(searchWindow->ui.actorBox,SIGNAL(textChanged()),this,SLOT(on_actorBox_textChanged()));
    connect(searchWindow->ui.yearSlider,SIGNAL(valueChanged(int)),this,SLOT(on_yearSlider_valueChanged(int)));
    connect(searchWindow->ui.yearPrecision,SIGNAL(valueChanged(int)),this,SLOT(on_yearPrecision_valueChanged(int)));
    connect(searchWindow->ui.directorBox,SIGNAL(textChanged()),this,SLOT(on_directorBox_textChanged()));
    connect(searchWindow->ui.timeSlider,SIGNAL(valueChanged(int)),this,SLOT(on_timeSlider_valueChanged(int)));
    connect(searchWindow->ui.timePrecision,SIGNAL(valueChanged(int)),this,SLOT(on_timePrecision_valueChanged(int)));

    //Initialisation de la grille :
    gridLayout = new QGridLayout;
    grid_colonne = 0;
    grid_ligne = 0;
    ui.scrollAreaWidgetContents->setLayout(gridLayout);

    //Initialisation du Network Manager :
    manager = new QNetworkAccessManager(this);
    //Lorsque la requ�te est fini, il envoie le signal finished qu'on connecte � un de nos slots pour g�rer la r�ponse
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(slotRequestFinished(QNetworkReply*)));

}
//TEST
FilmFinder::~FilmFinder()
{

}

//affiche la fen�tre avec les param�tres avanc�s
void FilmFinder::showAdvancedSearch()
{
	dock->show();
}
void FilmFinder::search()//On effectue notre requete de recherche (� appeler � chaque modification dans notre recherche avanc�e)
{
	cout<<"search ..."<<endl;
	/*QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // L'ip du host
    db.setUserName("root"); // Ton login
    db.setPassword(""); // Ton password
    db.setDatabaseName("mydb"); //Le nom de ta database

    cout<<"Base SQL : "<< db.open() <<endl;
    QSqlQuery query;
    query.exec("SELECT * FROM td_film WHERE titre LIKE '%star%' ;");
    while(query.next()){
    	QWidget *film = new FilmView(this);
    	ajouterFilm(film);
    }
    db.close();
    */
	QUrl url = new QUrl("http://localhost/FilmFinder/film.php");
	//On donne au manager une req�te � effectuer. Lorsque cette requ�te est finie,
	//Il enverra la requ�te � slotRequestFinished
	 manager->get(QNetworkRequest(url));

}

void FilmFinder::on_yearSlider_valueChanged(int value){
    this->search();
}

void FilmFinder::on_yearPrecision_valueChanged(int arg1)//Faire une recherche sur l'ann�e (prendre en compte l'ann�e)
{
    this->search();
}


void FilmFinder::on_timeSlider_valueChanged(int value)//Faire une recherche sur la dur�e (prendre en compte la pr�cision)
{
    this->search();
}

void FilmFinder::on_timePrecision_valueChanged(int arg1)//Faire une recherche sur la dur�e (prendre en compte la dur�e)
{
    this->search();
}

void FilmFinder::on_actorBox_textChanged()//Faire une recherche sur les acteurs
{
    this->search();
}

void FilmFinder::on_directorBox_textChanged()//Faire une rechercher sur les r�alisateurs
{
    this->search();
}

void FilmFinder::on_searchBtn_clicked()//Faire une recherche sur les noms (Noms dans searchBox)
{
    this->search();
}

void FilmFinder::ajouterFilm(QWidget * film){
	gridLayout->addWidget(film,grid_ligne,grid_colonne);
	grid_colonne++;
	int nbre_col=GRID_NBRE_COL;
	if(grid_colonne==nbre_col){
		grid_ligne++;
		grid_colonne=0;
	}
}

//Traite la page renvoy�e par la recherche
void FilmFinder::slotRequestFinished(QNetworkReply * reply){
	QString rep= reply->readAll();
	cout <<"R�ponse : " <<rep.toStdString() <<endl;
	FilmView *film = new FilmView();
	film->setTitle(rep);
	ajouterFilm(film);
}
