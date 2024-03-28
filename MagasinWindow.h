#ifndef MAGASINWINDOW_H
#define MAGASINWINDOW_H

#include <QMainWindow>
#include <QLabel>
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
    void updateArgent();

private:
    void setupUi();
    Joueur *m_joueur;
    QLabel *labelArgent;

signals:
    void requestRefresh();
};

#endif // MAGASINWINDOW_H
