#include "advancedsearchwindow.h"
#include "ui_advancedsearchwindow.h"


AdvancedSearchWindow::AdvancedSearchWindow(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    //Initialisation du Network Manager :
    manager = new QNetworkAccessManager(this);
    //Lorsque la requ�te est fini, il envoie le signal finished qu'on connecte � un de nos slots pour g�rer la r�ponse
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(slotRequestFinished(QNetworkReply*)));

    QString urlString="http://perso.telecom-paristech.fr/~oudet/filmfinder/getGenre.php";
    QUrl* url = new QUrl(urlString);
    //On donne au manager une req�te � effectuer. Lorsque cette requ�te est finie,
    //Il enverra la requ�te � slotRequestFinished
    manager->get(QNetworkRequest(*url));

}

AdvancedSearchWindow::~AdvancedSearchWindow()
{

}

void AdvancedSearchWindow::on_yearSlider_valueChanged(int value)//Faire une recherche sur l'ann�e
{
    QString v;
    v.setNum(value);
    ui.yearValue->setText(v);

}

void AdvancedSearchWindow::on_timeSlider_valueChanged(int value)//Faire une recherche sur la dur�e (prendre en compte la pr�cision)
{
    QString v;
    v.setNum(value);
    ui.timeValue->setText(v);
}

void AdvancedSearchWindow::setNumberResult(int number){
    QString nombre(number);
    ui.resultNumber->setText(nombre);
}

//Traite la page renvoy�e par la recherche
void AdvancedSearchWindow::slotRequestFinished(QNetworkReply * reply) {
    QString rep = reply->readAll();

    QString prems = rep.at(0);
    if(prems.toStdString() != "[" ){
        rep.remove(0,1);

    }

    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate(rep);

    //Si on a bien re�u un array
    if (sc.isArray()) {
        QScriptValueIterator it(sc);
        //On it�re sur le tableau
        while (it.hasNext()) {
            it.next();
            QString genre = it.value().property("genre").toString();
            if (genre!=""){
                this->ui.genreComboBox->addItem(genre);
            }

        }
    }

}
