#include "EquipeWindow.h"

EquipeWindow::EquipeWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
}

EquipeWindow::~EquipeWindow()
{
    // Libérez les ressources si nécessaire
}

void EquipeWindow::setupUi()
{
    // Implémentez ici la mise en page de l'interface utilisateur pour la fenêtre de l'équipe
    // Ajoutez des boutons, des étiquettes, etc., pour afficher les pokemon de l'équipe et leurs informations
}

void EquipeWindow::changerPokemon()
{
    // Implémentez l'action de changer de pokemon ici
    // Par exemple, changez le pokemon actuellement en jeu avec un autre pokemon de l'équipe
}
