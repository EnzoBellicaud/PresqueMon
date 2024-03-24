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

void EquipeWindow::setupUi()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *layout = new QGridLayout(centralWidget);

    // Parcourir la liste des pokemons du joueur
    int row = 0;
    int col = 0;
    for (int i = 0; i < m_joueur->getPokemon().size(); ++i) {
        Pokemon pokemon = m_joueur->getPokemon()[i];
        // Créer un bouton pour chaque pokemon
        QPushButton *button = new QPushButton(pokemon.getName(), centralWidget);
        layout->addWidget(button, row, col);
        // Connecter le clic du bouton à la fonction changerPokemon
        connect(button, &QPushButton::clicked, [=]() {
            changerPokemon(i);
        });

        ++col;
        if (col == 2) {
            col = 0;
            ++row;
        }
    }

    // Ajouter un bouton Retour
    QPushButton *boutonRetour = new QPushButton("Retour", centralWidget);
    layout->addWidget(boutonRetour, row + 1, 0, 1, 2);
    connect(boutonRetour, &QPushButton::clicked, this, &EquipeWindow::close);

    setWindowTitle("Équipe");
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
    close();
}
