#include "MagasinWindow.h"

MagasinWindow::MagasinWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
}

MagasinWindow::~MagasinWindow()
{
    // Libérez les ressources si nécessaire
}

void MagasinWindow::setupUi()
{
    // Implémentez ici la mise en page de l'interface utilisateur pour la fenêtre du magasin
    // Ajoutez des boutons, des étiquettes, etc., pour les potions, les objets, etc.
}

void MagasinWindow::acheterPotion()
{
    // Implémentez l'action d'achat d'une potion ici
    // Par exemple, augmentez le nombre de potions du joueur et déduisez l'argent
}
