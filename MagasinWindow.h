#ifndef MAGASINWINDOW_H
#define MAGASINWINDOW_H

#include <QMainWindow>
#include "Joueur.h"

class MagasinWindow : public QMainWindow
{
    Q_OBJECT

public:
    MagasinWindow(Joueur *joueur, QWidget *parent = nullptr);
    ~MagasinWindow();

public slots:
    void acheterPetitePotion();
    void acheterMoyennePotion();

private:
    void setupUi();
    Joueur *m_joueur;
};

#endif // MAGASINWINDOW_H
