#ifndef EQUIPEWINDOW_H
#define EQUIPEWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include "Joueur.h"

class EquipeWindow : public QMainWindow
{
    Q_OBJECT

public:
    EquipeWindow(Joueur *joueur, QWidget *parent = nullptr);
    ~EquipeWindow();
    void updatePokemon();

private:
    Joueur *m_joueur;
    QGridLayout *layout;

    void setupUi();
    void changerPokemon(int index);
    
signals:
    void requestRefresh();
};

#endif // EQUIPEWINDOW_H
