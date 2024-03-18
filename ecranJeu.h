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

class ecranJeu : public QMainWindow
{
    Q_OBJECT

public:
    explicit ecranJeu(QWidget *parent = nullptr);
    ~ecranJeu();

private:
    QWidget *centralwidget;
    QVBoxLayout *ecranJeuLayout;
    QHBoxLayout *zoneCombatLayout;
    QVBoxLayout *monstreJoueurLayout;
    QFrame *imageJoueur;
    QProgressBar *vieJoueur;
    QVBoxLayout *monstreAdversaireLayout;
    QProgressBar *vieAdversaire;
    QFrame *imageAdversaire;
    QHBoxLayout *zoneChoixLayout;
    QScrollArea *combatInfo;
    QWidget *combatInfoContent;
    QGridLayout *grilleOptions;
    QPushButton *boutonEquipe;
    QPushButton *boutonFuite;
    QPushButton *boutonAttaque;
    QPushButton *boutonSac;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi();
    void retranslateUi();

private slots:
    // Ajoutez des slots si nécessaire
};

#endif // ECRANJEU_H
