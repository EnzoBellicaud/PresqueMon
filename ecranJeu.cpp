#include "ecranJeu.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>

ecranJeu::ecranJeu(QWidget *parent) : QMainWindow(parent)
{
    joueur = new Joueur();
    adversaire = new Adversaire();

    pokemonJoueur = new Pokemon(); 
    pokemonAdversaire = new Pokemon();

    magasinWindow = new MagasinWindow(joueur,this);
    equipeWindow = new EquipeWindow(joueur, this);
    
    setupGamePlay();
    setupUi(); 
}

ecranJeu::~ecranJeu()
{
    delete joueur;
    delete adversaire;
    delete pokemonJoueur;
    delete pokemonAdversaire;
    delete magasinWindow;
    delete equipeWindow;
}

void ecranJeu::setupGamePlay()
{
    joueur->initializeFromJson();
    adversaire->initializeFromJson();
    
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
    labelImageJoueur = new QLabel();
    labelImageJoueur->setPixmap(QPixmap(pokemonJoueur->getImageDos()).scaled(100, 100, Qt::KeepAspectRatio));
    vieJoueur = new QProgressBar();

    vieJoueur->setValue((pokemonJoueur->getPV() * 100) / pokemonJoueur->getPVMax());

    monstreJoueurLayout->addWidget(labelImageJoueur);
    monstreJoueurLayout->addWidget(vieJoueur);

    

    monstreAdversaireLayout = new QVBoxLayout();
    vieAdversaire = new QProgressBar();
    labelImageAdversaire = new QLabel();
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
    combatInfoText = new QTextEdit();
    combatInfoText->setReadOnly(true); // Pour rendre le texte non modifiable
    combatInfoText->setPlaceholderText("Actions de la partie");


    zoneChoixLayout->addWidget(combatInfoText);

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

    connect(magasinWindow, &MagasinWindow::requestRefresh, this, &ecranJeu::updateScene);
}

void ecranJeu::ouvrirMagasin()
{
    //this->setDisabled(true);
    magasinWindow->updateArgent();
    magasinWindow->show();
}

void ecranJeu::ouvrirEquipe()
{
    //this->setDisabled(true);
    equipeWindow->updatePokemon();
    equipeWindow->show();
}

void ecranJeu::attaque()
{
    int vitesseJoueur = pokemonJoueur->getSpeed();
    int vitesseAdversaire = pokemonAdversaire->getSpeed();

    if (vitesseJoueur >= vitesseAdversaire) {
        combatInfoText->append(pokemonJoueur->getName() + " attaque le " + pokemonAdversaire->getName() + " adverse !");
        int degats = 20 * (pokemonJoueur->getAttack() / pokemonAdversaire->getDefense());
        pokemonAdversaire->addPV(-degats);
        vieAdversaire->setValue((pokemonAdversaire->getPV() * 100) / pokemonAdversaire->getPVMax());
        if (pokemonAdversaire->getPV() <= 0){
            combatInfoText->append("Le "+pokemonAdversaire->getName() + " adverse est KO !");
            if (adversaire->finCombat()){
                combatInfoText->append("L'adversaire n'a plus de pokémon, vous avez gagné !");
                victoireJoueur(true);
            } else {
                pokemonAdversaire = adversaire->getFirstPokemon();
                combatInfoText->append("L'adversaire envoie un "+pokemonAdversaire->getName() + " !");
            }
        } else {
            combatInfoText->append("Le "+pokemonAdversaire->getName() + " adverse attaque  " + pokemonJoueur->getName() + " !");
            int degats = 20 * (pokemonAdversaire->getAttack() / pokemonJoueur->getDefense());
            pokemonJoueur->addPV(-degats);
            vieJoueur->setValue((pokemonJoueur->getPV() * 100) / pokemonJoueur->getPVMax());
            if (pokemonJoueur->getPV() <= 0){
                combatInfoText->append("Votre "+pokemonJoueur->getName() + " est KO !");
                if (joueur->finCombat()){
                    combatInfoText->append("Vous avez perdu... Vos pokémons ont souffert");
                    victoireJoueur(false);
                } else {
                    pokemonJoueur = joueur->getFirstPokemon();
                    combatInfoText->append(pokemonJoueur->getName() + " entre sur le terrain !");
                }
            }
        }
    } else {
        combatInfoText->append("Le "+pokemonAdversaire->getName() + " adverse attaque  " + pokemonJoueur->getName() + " !");
        int degats = 20 * (pokemonAdversaire->getAttack() / pokemonJoueur->getDefense());
        pokemonJoueur->addPV(-degats);
        vieJoueur->setValue((pokemonJoueur->getPV() * 100) / pokemonJoueur->getPVMax());
        if (pokemonJoueur->getPV() <= 0){
            combatInfoText->append("Votre "+pokemonJoueur->getName() + " est KO !");
            if (joueur->finCombat()){
                combatInfoText->append("Vous avez perdu... Vos pokémons ont souffert");
                victoireJoueur(false);
            } else {
                pokemonJoueur = joueur->getFirstPokemon();
                combatInfoText->append(pokemonJoueur->getName() + " entre sur le terrain !");
            }
        } else {
            combatInfoText->append(pokemonJoueur->getName() + " attaque le " + pokemonAdversaire->getName() + " adverse !");
            int degats = 20 * (pokemonJoueur->getAttack() / pokemonAdversaire->getDefense());
            pokemonAdversaire->addPV(-degats);
            vieAdversaire->setValue((pokemonAdversaire->getPV() * 100) / pokemonAdversaire->getPVMax());
            if (pokemonAdversaire->getPV() <= 0){
                combatInfoText->append("Le "+pokemonAdversaire->getName() + " adverse est KO !");
                if (adversaire->finCombat()){
                    combatInfoText->append("L'adversaire n'a plus de pokémon, vous avez gagné !");
                    victoireJoueur(true);
                } else {
                    pokemonAdversaire = adversaire->getFirstPokemon();
                    combatInfoText->append("L'adversaire envoie un "+pokemonAdversaire->getName() + " !");
                }
            }
        }
    }
    updateScene();
}

void ecranJeu::victoireJoueur(bool win)
{
    if (win){
        joueur->addMoney(100);
        combatInfoText->append("Vous avez gagné 100$ !");
    } else {
        joueur->addMoney(-100);
        combatInfoText->append("Vous avez perdu 100$ !");
        showGameOverPopup();
    }
}

void ecranJeu::updateScene()
{
    vieJoueur->setValue((pokemonJoueur->getPV() * 100) / pokemonJoueur->getPVMax());
    labelImageJoueur->setPixmap(QPixmap(pokemonJoueur->getImageDos()).scaled(100, 100, Qt::KeepAspectRatio));
    vieAdversaire->setValue((pokemonAdversaire->getPV() * 100) / pokemonAdversaire->getPVMax());
    labelImageAdversaire->setPixmap(QPixmap(pokemonAdversaire->getImageFace()).scaled(100, 100, Qt::KeepAspectRatio));
    combatInfoText->append("--------------------------");
}

void ecranJeu::saveGame()
{
    joueur->saveToJson();
    adversaire->saveToJson();
}

void ecranJeu::showGameOverPopup() {
    QMessageBox msgBox;
    msgBox.setText("Vous avez perdu !");
    msgBox.setInformativeText("Que voulez-vous faire ?");
    msgBox.addButton("Recommencer", QMessageBox::AcceptRole);
    msgBox.addButton("Repartir à la dernière sauvegarde", QMessageBox::RejectRole);
    msgBox.setDefaultButton(QMessageBox::NoButton); // Pour éviter la sélection par défaut

    int choice = msgBox.exec();

    if (choice == QMessageBox::AcceptRole) {
        // Réinitialiser l'état du jeu
        resetGame();
    } else if (choice == QMessageBox::RejectRole) {
        // Charger les données de la dernière sauvegarde
        loadLastSave();
    }
}

void ecranJeu::resetGame() {
    // Réinitialiser les données du joueur et de l'adversaire
    joueur->initializeTestData(joueur->getPseudo());
    adversaire->initializeTestData();
    // Mettre à jour l'interface utilisateur en conséquence
    loadLastSave();
}

void ecranJeu::loadLastSave() {
    // Charger les données de la dernière sauvegarde
    joueur->initializeFromJson();
    adversaire->initializeFromJson();
    // Mettre à jour l'interface utilisateur en conséquence
    updateScene();
}