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
#include <QTextEdit>
#include <QPixmap>
#include <QLabel>
#include "MagasinWindow.h"
#include "EquipeWindow.h"
#include "Joueur.h"
#include "Adversaire.h"
#include "Pokemon.h"

class ecranJeu : public QMainWindow
{
    Q_OBJECT

public:
    explicit ecranJeu(QWidget *parent = nullptr);
    ~ecranJeu();
    void saveGame();
    void setupUi();
    void setupGamePlay();

private:
    QWidget *centralWidget;
    QVBoxLayout *ecranJeuLayout;

    // Zone Combat
    QHBoxLayout *zoneCombatLayout;
    QVBoxLayout *monstreJoueurLayout;
    QVBoxLayout *monstreAdversaireLayout;
    QProgressBar *vieJoueur;
    QProgressBar *vieAdversaire;
    QLabel *labelImageJoueur;
    QLabel *labelImageAdversaire;

    // Zone Choix
    QHBoxLayout *zoneChoixLayout;
    QScrollArea *combatInfo;
    QTextEdit *combatInfoText;
    QGridLayout *grilleOptions;
    QPushButton *boutonEquipe;
    QPushButton *boutonFuite;
    QPushButton *boutonAttaque;
    QPushButton *boutonSac;

    Joueur *joueur;
    Adversaire *adversaire;
    Pokemon *pokemonJoueur;
    Pokemon *pokemonAdversaire;
    MagasinWindow *magasinWindow;
    EquipeWindow *equipeWindow;

    void resetGame();
    void loadLastSave();
    

private slots:
    void ouvrirMagasin();
    void ouvrirEquipe();
    void attaque();
    void victoireJoueur(bool win);
    void updateScene();
    void showGameOverPopup();

signals:
    void resetGameClicked();
};

#endif // ECRANJEU_H
