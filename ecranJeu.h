#ifndef ECRANJEU_H
#define ECRANJEU_H

#include <QApplication>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMenuBar>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include "MagasinWindow.h"
#include "EquipeWindow.h"
#include "Joueur.h"
#include "Pokemon.h"

class ecranJeu : public QMainWindow
{
    Q_OBJECT

public:
    explicit ecranJeu(QWidget *parent = nullptr);
    ~ecranJeu();

private:
    QWidget *centralWidget;
    QVBoxLayout *ecranJeuLayout;


    // Zone Combat
    QHBoxLayout *zoneCombatLayout;
    QVBoxLayout *monstreJoueurLayout;
    QVBoxLayout *monstreAdversaireLayout;
    QProgressBar *vieJoueur;
    QProgressBar *vieAdversaire;

    // Zone Choix
    QHBoxLayout *zoneChoixLayout;
    QScrollArea *combatInfo;
    QWidget *combatInfoContent;
    QGridLayout *grilleOptions;
    QPushButton *boutonEquipe;
    QPushButton *boutonFuite;
    QPushButton *boutonAttaque;
    QPushButton *boutonSac;

    Joueur *joueur;
    Joueur *adversaire;
    Pokemon *pokemonJoueur;
    Pokemon *pokemonAdversaire;
    MagasinWindow *magasinWindow;
    EquipeWindow *equipeWindow;

    void setupUi();
    void setupGamePlay();
    int calculerDegats(const Pokemon& attaquant, const Pokemon& defenseur);

private slots:
    void ouvrirMagasin();
    void ouvrirEquipe();
    void attaque();
};

#endif // ECRANJEU_H
