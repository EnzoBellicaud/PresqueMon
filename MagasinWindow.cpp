#include "MagasinWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <iostream>


MagasinWindow::MagasinWindow(Joueur *joueur, QWidget *parent) : QMainWindow(parent), m_joueur(joueur)
{
    setupUi();
}

MagasinWindow::~MagasinWindow()
{
}

void MagasinWindow::setupUi()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    // Création des étiquettes pour les potions
    labelArgent = new QLabel("");
    QLabel *labelPetitePotion = new QLabel("Petite Potion 20$");
    QLabel *labelMoyennePotion = new QLabel("Moyenne Potion 50$");

    // Création des boutons pour acheter les potions
    QPushButton *boutonAcheterPetitePotion = new QPushButton("Acheter");
    QPushButton *boutonAcheterMoyennePotion = new QPushButton("Acheter");

    // Connexion des signaux et des slots pour les boutons d'achat
    connect(boutonAcheterPetitePotion, &QPushButton::clicked, this, &MagasinWindow::acheterPetitePotion);
    connect(boutonAcheterMoyennePotion, &QPushButton::clicked, this, &MagasinWindow::acheterMoyennePotion);

    // Ajout des étiquettes et des boutons au layout
    layout->addWidget(labelArgent);
    layout->addWidget(labelPetitePotion);
    layout->addWidget(boutonAcheterPetitePotion);
    layout->addWidget(labelMoyennePotion);
    layout->addWidget(boutonAcheterMoyennePotion);

    // Bouton de retour
    QPushButton *boutonRetour = new QPushButton("Retour");
    connect(boutonRetour, &QPushButton::clicked, this, &MagasinWindow::close);

    // Ajout du bouton de retour au layout
    layout->addWidget(boutonRetour);

    setWindowTitle("Magasin");
}

void MagasinWindow::acheterPetitePotion()
{
    if (m_joueur->getMoney() >= 20)
    {
        m_joueur->addMoney(-20);
        updateArgent();
        m_joueur->getPokemonFighting()->addPV(20);
        emit requestRefresh();
    }
    else
    {
        QMessageBox::warning( 
            this, 
            tr("Vendeur"), 
            tr("Vous n'avez pas assez d'argent !") );

    }
}

void MagasinWindow::acheterMoyennePotion()
{
    if (m_joueur->getMoney() >= 50)
    {
        m_joueur->addMoney(-50);
        updateArgent();
        m_joueur->getPokemonFighting()->addPV(40);
        emit requestRefresh();
    }
    else
    {
        QMessageBox::warning( 
            this, 
            tr("Vendeur"), 
            tr("Vous n'avez pas assez d'argent !") );

    }
}

void MagasinWindow::updateArgent()
{
    labelArgent->setText("Vous avez " + QString::number(m_joueur->getMoney()) + "$");
}
