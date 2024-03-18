#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

#include "PageAccueil.h"
#include "PageGame.h"
#include "PageRegister.h"
#include "ecranJeu.h"
#include "Joueur.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void save();
    void about();
    void aboutQt();
    void showPageAccueil();
    void showPageGame();
    void showPageRegister();
    void showEcranJeu();

private:
    QStackedWidget *stackedWidget;
    PageAccueil *pageAccueil;
    PageGame *pageGame;
    PageRegister *pageRegister;
    ecranJeu *pageEcranJeu;
    Joueur *joueur;

    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QAction *saveAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;
    QPushButton *buttonNouvellePartie;
    QPushButton *buttonChargerPartie;
};

#endif