#include "filmfinder.h"

FilmFinder::FilmFinder(QWidget *parent) :
    QMainWindow(parent) {
    ui.setupUi(this);
    searchWindow = new AdvancedSearchWindow();
    setWindowTitle("FilmFinder");
    this->showMaximized();

    this->title="";
    this->actor="";
    this->director="";
    this->year=-1;
    this->yearPrecision=-1;
    this->time=-1;
    this->timePrecision=-1;

    //Ou on fait un bouton pour ouvrir une nouvelle fenetre
    QPushButton *advancedSearchButton = ui.pushButton;

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
    connect(ui.searchBox, SIGNAL(returnPressed()), this, SLOT(onEnterPressed()));

    //Fenetre de recherche avancée
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
    connect(searchWindow->ui.clearButton, SIGNAL(clicked()),this,SLOT(on_clearButton_clicked()));


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
    this->search();

}
//TEST
FilmFinder::~FilmFinder() {

}

//affiche la fenêtre avec les paramètres avancés
void FilmFinder::showAdvancedSearch() {
    if(dock->isHidden()) dock->show();
    else dock->hide();
}
void FilmFinder::search() //On effectue notre requete de recherche (à appeler à chaque modification dans notre recherche avancée)
{
    //cout << "search ..." << endl;
    ui.searching->show();

    viderGrille();
    //this->year=2011;
    QString param= "";
    param+= "year="+QString::number(this->year);
    param+= "&title="+this->title;
    param+= "&time="+QString::number(this->time);
    param+= "&yearPrecision="+QString::number(this->yearPrecision);
    param+= "&timePrecision="+QString::number(this->timePrecision);
    param+= "&actor="+this->actor;
    param+= "&director="+this->director;
    QString urlString="http://perso.telecom-paristech.fr/~oudet/filmfinder/film.php?"+param;
    cout<<urlString.toStdString()<<endl;
    QUrl* url = new QUrl(urlString);
    //On donne au manager une reqête à effectuer. Lorsque cette requête est finie,
    //Il enverra la requête à slotRequestFinished
    manager->get(QNetworkRequest(*url));

}

void FilmFinder::on_yearSlider_valueChanged(int value) {
    this->year=value;
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
    this->title=this->ui.searchBox->text();
    cout<<this->title.toStdString()<<endl;
    this->search();
}

void FilmFinder::onEnterPressed(){
    this->on_searchBtn_clicked();
    cout<<"Enter pressed"<<endl;
}

void FilmFinder::on_clearButton_clicked(){
    searchWindow->ui.actorBox->clear();
    searchWindow->ui.directorBox->clear();
    searchWindow->ui.resultNumber->clear();
    searchWindow->ui.timePrecision->clear();
    searchWindow->ui.yearPrecision->clear();
    searchWindow->ui.yearSlider->setValue(1920);
    searchWindow->ui.timeSlider->setValue(0);
    this->title="";
    this->actor="";
    this->director="";
    this->year=-1;
    this->yearPrecision=-1;
    this->time=-1;
    this->timePrecision=-1;
    this->viderGrille();

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
    this->viderGrille();
    QString rep = reply->readAll();
    cout << "Réponse : " << rep.toStdString() << endl;

    QString prems = rep.at(0);
    cout << "premier char : " << prems.toStdString() << endl;
    if(prems.toStdString() != "[" ){
    	rep.remove(0,1);
        cout << "Réponse modifiée: " << rep.toStdString() << endl;

    }

    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate(rep);
    int number = 0;

    //Si on a bien reçu un array
    if (sc.isArray()) {
        QScriptValueIterator it(sc);
        //On itère sur le tableau
        while (it.hasNext()) {
            it.next();

            FilmView *film = new FilmView();
            QString titre = it.value().property("titre").toString();
            QString annee = it.value().property("annee").toString();
            QString duree = it.value().property("duree").toString();
            QString image = it.value().property("image").toString();

            if(it.value().property("actor").isArray()){
                QScriptValueIterator it_actor(it.value().property("actor"));
                QList<QString> acteurs;

                while(it_actor.hasNext()){
                    it_actor.next();
                    if(it_actor.value().property("prenom_acteur").toString()!=""){
                        acteurs.append(it_actor.value().property("prenom_acteur").toString()+ " " +
                                       it_actor.value().property("nom_acteur").toString());
                    }

                }
                //cout<<acteurs.size()<<endl;

                film->setActeurs(acteurs);
            }
            if(it.value().property("director").isArray()){
                QScriptValueIterator it_director(it.value().property("director"));
                QList<QString> directors;

                while(it_director.hasNext()){
                    it_director.next();
                    if(it_director.value().property("prenom_realisateur").toString()!=""){
                        directors.append(it_director.value().property("prenom_realisateur").toString()+ " " +
                                         it_director.value().property("nom_realisateur").toString());
                    }

                }
                film->setDirectors(directors);
            }
            if(it.value().property("genre").isArray()){
                QScriptValueIterator it_genre(it.value().property("genre"));
                QList<QString> genres;

                while(it_genre.hasNext()){
                    it_genre.next();
                    if(it_genre.value().property("genre").toString()!=""){
                        genres.append(it_genre.value().property("genre").toString());
                    }
                }
                film->setGenres(genres);
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
            if (image != "" && image != "null") {
                film->setImage(image);
            }
            if(titre != ""){
                number++;
                ajouterFilm(film);
            }
        }

    }

    searchWindow->ui.resultNumber->setText(QString::number(number));
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
