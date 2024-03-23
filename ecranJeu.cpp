#include "ecranJeu.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ecranJeu::ecranJeu(QWidget *parent) : QMainWindow(parent)
{
    setupGamePlay();
    setupUi();
    
    magasinWindow = new MagasinWindow(this);
    equipeWindow = new EquipeWindow(this);
}

ecranJeu::~ecranJeu()
{
    delete magasinWindow;
    delete equipeWindow;
}

void ecranJeu::setupGamePlay()
{
    QString filePath = "data/data.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier.";
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError parseError; // Déclaration de QJsonParseError
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError); // Correction ici : jsonData au lieu de byteArray
    if (parseError.error != QJsonParseError::NoError) { // Vérifier si une erreur de parse est survenue
        qDebug() << "Erreur lors du parsing du JSON :" << parseError.errorString();
        return;
    }
    
    QJsonObject jsonObj  = jsonDoc.object();

    joueur = new Joueur();
    adversaire = new Joueur();
    joueur->initializeFromJson(jsonObj);
    adversaire->initializeFromJson(jsonObj);
    pokemonJoueur = new Pokemon(); 
    pokemonAdversaire = new Pokemon();
    pokemonJoueur = joueur->getFirstPokemon();
    pokemonAdversaire = adversaire->getFirstPokemon();

}


void ecranJeu::setupUi()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    ecranJeuLayout = new QVBoxLayout(centralWidget);
    ecranJeuLayout->setContentsMargins(0, 0, 0, 0);

    //------------------------------- Zone Combat ---------------------------------

    zoneCombatLayout = new QHBoxLayout();

    monstreJoueurLayout = new QVBoxLayout();
    QLabel *labelImageJoueur = new QLabel();
    labelImageJoueur->setPixmap(QPixmap(pokemonJoueur->getImageDos()).scaled(100, 100, Qt::KeepAspectRatio));
    vieJoueur = new QProgressBar();

    vieJoueur->setValue((pokemonJoueur->getPV() * 100) / pokemonJoueur->getPVMax());

    monstreJoueurLayout->addWidget(labelImageJoueur);
    monstreJoueurLayout->addWidget(vieJoueur);

    

    monstreAdversaireLayout = new QVBoxLayout();
    vieAdversaire = new QProgressBar();
    QLabel *labelImageAdversaire = new QLabel();
    labelImageAdversaire->setPixmap(QPixmap(pokemonAdversaire->getImageFace()).scaled(100, 100, Qt::KeepAspectRatio));
    vieAdversaire->setValue((pokemonAdversaire->getPV() * 100) / pokemonAdversaire->getPVMax());

    monstreAdversaireLayout->addWidget(vieAdversaire);
    monstreAdversaireLayout->addWidget(labelImageAdversaire);

    zoneCombatLayout->addLayout(monstreJoueurLayout);
    zoneCombatLayout->addStretch();
    zoneCombatLayout->addLayout(monstreAdversaireLayout);

    //------------------------------- Zone Choix ---------------------------------

    zoneChoixLayout = new QHBoxLayout();

    combatInfo = new QScrollArea();
    combatInfoContent = new QWidget();
    combatInfoContent->setGeometry(QRect(0, 0, 531, 420));
    combatInfoContent->setMinimumSize(QSize(531, 0));
    combatInfo->setWidget(combatInfoContent);

    zoneChoixLayout->addWidget(combatInfo);

    grilleOptions = new QGridLayout();
    boutonEquipe = new QPushButton();
    boutonFuite = new QPushButton();
    boutonAttaque = new QPushButton();
    boutonSac = new QPushButton();

    grilleOptions->addWidget(boutonEquipe, 1, 2, 1, 1);
    grilleOptions->addWidget(boutonFuite, 1, 0, 1, 1);
    grilleOptions->addWidget(boutonAttaque, 0, 0, 1, 1);
    grilleOptions->addWidget(boutonSac, 0, 2, 1, 1);

    zoneChoixLayout->addLayout(grilleOptions);

    ecranJeuLayout->addLayout(zoneCombatLayout);
    ecranJeuLayout->addLayout(zoneChoixLayout);

    boutonEquipe->setText("Equipe");
    connect(boutonEquipe, &QPushButton::clicked, this, &ecranJeu::ouvrirEquipe);
    boutonFuite->setText("Fuite");
    boutonAttaque->setText("Attaque");
    connect(boutonAttaque, &QPushButton::clicked, this, &ecranJeu::attaque);
    boutonSac->setText("Magasin");
    connect(boutonSac, &QPushButton::clicked, this, &ecranJeu::ouvrirMagasin);
}

void ecranJeu::ouvrirMagasin()
{
    magasinWindow->show();
}

void ecranJeu::ouvrirEquipe()
{
    equipeWindow->show();
}

void ecranJeu::attaque()
{
    int vitesseJoueur = pokemonJoueur->getSpeed();
    int vitesseAdversaire = pokemonAdversaire->getSpeed();

    if (vitesseJoueur >= vitesseAdversaire) {
        int degats = pokemonJoueur->getAttack() * (pokemonJoueur->getAttack() / pokemonAdversaire->getDefense());
        pokemonAdversaire->addPV(-degats);

        if (pokemonAdversaire->getPV() <= 0){
            if (adversaire->finCombat()){
                //finCombat(true);
            } else {
                pokemonAdversaire = adversaire->getFirstPokemon();
            }
        } else {
            int degats = pokemonAdversaire->getAttack() * (pokemonAdversaire->getAttack() / pokemonJoueur->getDefense());
            pokemonJoueur->addPV(-degats);
            if (pokemonJoueur->getPV() <= 0){
                if (joueur->finCombat()){
                    //finCombat(true);
                } else {
                    pokemonJoueur = joueur->getFirstPokemon();
                }
            }
        }
    } else {
        int degats = pokemonAdversaire->getAttack() * (pokemonAdversaire->getAttack() / pokemonJoueur->getDefense());
        pokemonJoueur->addPV(-degats);

        if (pokemonJoueur->getPV() <= 0){
            if (joueur->finCombat()){
                //finCombat(true);
            } else {
                pokemonJoueur = joueur->getFirstPokemon();
            }
        } else {
            int degats = pokemonJoueur->getAttack() * (pokemonJoueur->getAttack() / pokemonAdversaire->getDefense());
            pokemonAdversaire->addPV(-degats);
            if (pokemonAdversaire->getPV() <= 0){
                if (adversaire->finCombat()){
                    //finCombat(true);
                } else {
                    pokemonAdversaire = adversaire->getFirstPokemon();
                }
            }
        }
    }
}