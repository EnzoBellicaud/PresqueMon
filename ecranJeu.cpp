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
    QLabel *labelImageJoueur = new QLabel();
    labelImageJoueur->setPixmap(QPixmap("data/pokemon1.png").scaled(100, 100, Qt::KeepAspectRatio));
    vieJoueur = new QProgressBar();

    vieJoueur->setValue(100);

    monstreJoueurLayout->addWidget(labelImageJoueur);
    monstreJoueurLayout->addWidget(vieJoueur);

    

    monstreAdversaireLayout = new QVBoxLayout();
    vieAdversaire = new QProgressBar();
    QLabel *labelImageAdversaire = new QLabel();
    labelImageAdversaire->setPixmap(QPixmap("data/pokemon2.png").scaled(100, 100, Qt::KeepAspectRatio));
    vieAdversaire->setValue(100);

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
    boutonFuite->setText("Fuite");
    boutonAttaque->setText("Attaque");
    boutonSac->setText("Sac");
}

void ecranJeu::retranslateUi()
{
    setWindowTitle("MainWindow");
}
