#include "EquipeWindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

EquipeWindow::EquipeWindow(Joueur *joueur, QWidget *parent) : QMainWindow(parent), m_joueur(joueur)
{
    setupUi();
}

EquipeWindow::~EquipeWindow()
{
    // Libérez les ressources si nécessaire
}

void EquipeWindow::changerPokemon(int index)
{   
    if (index == m_joueur->getIdPokemonFighting()) {
        QMessageBox::information( 
            this, 
            tr("Impossible de changer de Pokémon"), 
            tr("%1 est déjà en combat.").arg(m_joueur->getPokemon()[index].getName()));
    }
    m_joueur->setIdPokemonFighting(index);
    emit requestRefresh();
    close();
}

void EquipeWindow::setupUi()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QGridLayout(centralWidget);

    // Créer les boutons pour chaque Pokémon
    for (int i = 0; i < 6; ++i) {
        QPushButton *boutonPokemon = new QPushButton("...", centralWidget);
        layout->addWidget(boutonPokemon, i / 2, i % 2); // Ajout du bouton au layout
        connect(boutonPokemon, &QPushButton::clicked, this, [this, i](){ changerPokemon(i); }); // Connecter le clic du bouton à changerPokemon
    }

    // Ajouter un bouton Retour
    QPushButton *boutonRetour = new QPushButton("Retour", centralWidget);
    layout->addWidget(boutonRetour, 3, 0, 1, 2); // Ajouter le bouton de retour
    connect(boutonRetour, &QPushButton::clicked, this, &EquipeWindow::close);

    setWindowTitle("Équipe");
}

void EquipeWindow::updatePokemon()
{
    // Mettre à jour l'affichage des Pokémon
    for (int i = 0; i < 6; ++i) {
        QPushButton *boutonPokemon = qobject_cast<QPushButton*>(layout->itemAtPosition(i / 2, i % 2)->widget());
        if (boutonPokemon) {
            if (m_joueur->getPokemon().size() >= i + 1) {
                boutonPokemon->setText(m_joueur->getPokemon()[i].getName());
                if (m_joueur->getPokemon()[i].getPV()>0) {
                    boutonPokemon->setText(m_joueur->getPokemon()[i].getName());
                } else {
                    boutonPokemon->setText(m_joueur->getPokemon()[i].getName() + " (K.O.)");
                    boutonPokemon->setEnabled(false);
                }
                
            } else {
                boutonPokemon->setText("...");
                boutonPokemon->setEnabled(false);
            }
        }
    }
}

