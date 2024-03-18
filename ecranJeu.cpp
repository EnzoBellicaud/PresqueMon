#include "ecranJeu.h"

ecranJeu::ecranJeu(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
}

ecranJeu::~ecranJeu()
{
}

void ecranJeu::setupUi()
{
    centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);

    ecranJeuLayout = new QVBoxLayout(centralwidget);
    ecranJeuLayout->setContentsMargins(0, 0, 0, 0);

    //------------------------------- Zone Combat ---------------------------------

    zoneCombatLayout = new QHBoxLayout();

    monstreJoueurLayout = new QVBoxLayout();
    imageJoueur = new QFrame();
    vieJoueur = new QProgressBar();

    vieJoueur->setValue(100);

    monstreJoueurLayout->addWidget(imageJoueur);
    monstreJoueurLayout->addWidget(vieJoueur);

    zoneCombatLayout->addLayout(monstreJoueurLayout);

    monstreAdversaireLayout = new QVBoxLayout();
    vieAdversaire = new QProgressBar();
    imageAdversaire = new QFrame();

    vieAdversaire->setValue(100);

    monstreAdversaireLayout->addWidget(vieAdversaire);
    monstreAdversaireLayout->addWidget(imageAdversaire);

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
    boutonFuite->setText("Fuite");
    boutonAttaque->setText("Attaque");
    boutonSac->setText("Sac");
}

void ecranJeu::retranslateUi()
{
    setWindowTitle("MainWindow");
}
