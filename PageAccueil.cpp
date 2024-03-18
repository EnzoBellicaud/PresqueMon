#include "PageAccueil.h"
#include <QPushButton>
#include <QVBoxLayout>

PageAccueil::PageAccueil(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPushButton *buttonNouvellePartie = new QPushButton(tr("Nouvelle Partie"));
    QPushButton *buttonChargerPartie = new QPushButton(tr("Charger Partie"));

    mainLayout->addWidget(buttonNouvellePartie);
    mainLayout->addWidget(buttonChargerPartie);

    setLayout(mainLayout);

    connect(buttonNouvellePartie, &QPushButton::clicked, this, &PageAccueil::newGameButtonClicked);
    connect(buttonChargerPartie, &QPushButton::clicked, this, &PageAccueil::continueGameButtonClicked);
}

PageAccueil::~PageAccueil()
{
}


