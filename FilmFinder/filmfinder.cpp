#include "filmfinder.h"

FilmFinder::FilmFinder(QWidget *parent) :
    QMainWindow(parent) {
    ui.setupUi(this);
    searchWindow = new AdvancedSearchWindow();

    this->title="";
    this->actor="";
    this->director="";
    this->year=-1;
    this->yearPrecision=-1;
    this->time=-1;
    this->timePrecision=-1;

    //Ou on fait un bouton pour ouvrir une nouvelle fenetre
    QPushButton *advancedSearchButton = new QPushButton(
                QIcon(":/images/fleche.png"), "", this);
    ui.layout->addWidget(advancedSearchButton);

    //Ou on fait un dock sur le coté
    dock = new QDockWidget("Advanced Search", this);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setMinimumWidth(250);
    dock->setMaximumSize(250, 400);
    dock->setWidget(searchWindow);
    dock->hide();

    //Cas de la nouvelle fenetre
    connect(advancedSearchButton, SIGNAL(clicked()), this,
            SLOT(showAdvancedSearch()));

    connect(searchWindow->ui.actorBox, SIGNAL(textChanged()), this,
            SLOT(on_actorBox_textChanged()));
    connect(searchWindow->ui.yearSlider, SIGNAL(valueChanged(int)), this,
            SLOT(on_yearSlider_valueChanged(int)));
    connect(searchWindow->ui.yearPrecision, SIGNAL(valueChanged(int)), this,
            SLOT(on_yearPrecision_valueChanged(int)));
    connect(searchWindow->ui.directorBox, SIGNAL(textChanged()), this,
            SLOT(on_directorBox_textChanged()));
    connect(searchWindow->ui.timeSlider, SIGNAL(valueChanged(int)), this,
            SLOT(on_timeSlider_valueChanged(int)));
    connect(searchWindow->ui.timePrecision, SIGNAL(valueChanged(int)), this,
            SLOT(on_timePrecision_valueChanged(int)));

    //Initialisation de la grille :
    gridLayout = new QGridLayout;
    grid_colonne = 0;
    grid_ligne = 0;
    ui.scrollAreaWidgetContents->setLayout(gridLayout);

    //Initialisation du Network Manager :
    manager = new QNetworkAccessManager(this);
    //Lorsque la requête est fini, il envoie le signal finished qu'on connecte à un de nos slots pour gérer la réponse
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(slotRequestFinished(QNetworkReply*)));

    //Searching wheel :
    QMovie *anim = new QMovie(":/images/wheel.gif");
    QSize *size = new QSize(30,30);
    anim->setScaledSize(*(size));
    ui.searching->setMovie(anim);
    anim->start();
    ui.searching->hide();
}
//TEST
FilmFinder::~FilmFinder() {

}

//affiche la fenêtre avec les paramètres avancés
void FilmFinder::showAdvancedSearch() {
    dock->show();
}
void FilmFinder::search() //On effectue notre requete de recherche (à appeler à chaque modification dans notre recherche avancée)
{
    cout << "search ..." << endl;
    ui.searching->show();

    viderGrille();
    //this->year=2011;
    QString param= "";
    param+= "year="+QString::number(this->year);
    param+= "&title="+this->title;
    param+= "&time="+QString::number(this->time);
    param+= "&actor="+this->actor;
    param+= "&director="+this->director;
    QString urlString="http://localhost/FilmFinder/film.php?"+param;
    cout<<urlString.toStdString()<<endl;
    QUrl* url = new QUrl(urlString);
    //On donne au manager une reqête à effectuer. Lorsque cette requête est finie,
    //Il enverra la requête à slotRequestFinished
    manager->get(QNetworkRequest(*url));
    /*QUrl *url = new QUrl("http://localhost/FilmFinder/film.php?year=2011");
    //On donne au manager une reqête à effectuer. Lorsque cette requête est finie,
    //Il enverra la requête à slotRequestFinished
    manager->get(QNetworkRequest(*(url)));*/

}

void FilmFinder::on_yearSlider_valueChanged(int value) {
    this->year=value;
    // cout<<QString::number(this->year).toStdString()<<endl;
    this->search();
}

void FilmFinder::on_yearPrecision_valueChanged(int arg1) //Faire une recherche sur l'année (prendre en compte l'année)
{
    this->yearPrecision=arg1;
    this->search();
}

void FilmFinder::on_timeSlider_valueChanged(int value) //Faire une recherche sur la durée (prendre en compte la précision)
{
    this->time=value;
    this->search();
}

void FilmFinder::on_timePrecision_valueChanged(int arg1) //Faire une recherche sur la durée (prendre en compte la durée)
{
    this->timePrecision=arg1;
    this->search();
}

void FilmFinder::on_actorBox_textChanged() //Faire une recherche sur les acteurs
{
    this->actor=searchWindow->ui.actorBox->toPlainText();
    this->search();
}

void FilmFinder::on_directorBox_textChanged() //Faire une rechercher sur les réalisateurs
{
    this->director=searchWindow->ui.directorBox->toPlainText();
    this->search();
}

void FilmFinder::on_searchBtn_clicked() //Faire une recherche sur les noms (Noms dans searchBox)
{
    this->title=this->ui.searchBox->toPlainText();
    cout<<this->title.toStdString()<<endl;
    this->search();
}

void FilmFinder::ajouterFilm(QWidget * film) {
    gridLayout->addWidget(film, grid_ligne, grid_colonne);
    grid_colonne++;
    int nbre_col = GRID_NBRE_COL;
    if (grid_colonne == nbre_col) {
        grid_ligne++;
        grid_colonne = 0;
    }
}

//Traite la page renvoyée par la recherche
void FilmFinder::slotRequestFinished(QNetworkReply * reply) {
    QString rep = reply->readAll();
    cout << "Réponse : " << rep.toStdString() << endl;

    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate(rep);

    //Si on a bien reçu un array
    if (sc.isArray()) {
        QScriptValueIterator it(sc);
        //On itère sur le tableau
        while (it.hasNext()) {//Une itération de trop a chaque fois. Chercher pk!
            it.next();
            FilmView *film = new FilmView();
            QString titre = it.value().property("titre").toString();
            QString annee = it.value().property("annee").toString();
            QString duree = it.value().property("duree").toString();
            if(it.value().property("actor").isArray()){
                QScriptValueIterator it_actor(it.value().property("actor"));
                QList<QString> acteurs;

                while(it_actor.hasNext()){
                    it_actor.next();
                    acteurs.append(it_actor.value().property("prenom_acteur").toString()+ " " +
                                   it_actor.value().property("nom_acteur").toString());

                }
                //cout<<acteurs.size()<<endl;
                film->setActeurs(acteurs);
            }
            if(it.value().property("director").isArray()){
                QScriptValueIterator it_director(it.value().property("director"));
                QList<QString> directors;

                while(it_director.hasNext()){
                    it_director.next();
                    directors.append(it_director.value().property("prenom_realisateur").toString()+ " " +
                                   it_director.value().property("nom_realisateur").toString());

                }
                //cout<<acteurs.size()<<endl;
                film->setDirectors(directors);
            }
            if (titre != "") {
                film->setTitle(titre);
            }
            if (annee != "") {
                film->setYear(annee);
            }
            if (duree != "") {
                film->setTime(duree);
            }
            ajouterFilm(film);
        }

    }
    ui.searching->hide();

}

//Fonction pour vider la grille des précédents résultats
void FilmFinder::viderGrille(){
    if (gridLayout->layout() != NULL) {
        QLayoutItem *item;
        while ((item = gridLayout->layout()->takeAt(0)) != NULL) {
            delete item->widget();
            delete item;
        }
        delete gridLayout->layout();
        gridLayout = new QGridLayout;
        grid_colonne = 0;
        grid_ligne = 0;
        ui.scrollAreaWidgetContents->setLayout(gridLayout);
    }
}
