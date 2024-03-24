#ifndef EQUIPEWINDOW_H
#define EQUIPEWINDOW_H

#include <QMainWindow>
#include "Joueur.h"

class EquipeWindow : public QMainWindow
{
    Q_OBJECT

public:
    EquipeWindow(Joueur *joueur, QWidget *parent = nullptr);
    ~EquipeWindow();

private:
    Joueur *m_joueur;

    void setupUi();
    void changerPokemon(int index);

};

#endif // EQUIPEWINDOW_H
