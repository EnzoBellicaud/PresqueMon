#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "PageAccueil.h"
#include "PageGame.h"
#include "PageRegister.h"
#include "ecranJeu.h"
#include "Joueur.h"
#include "MusicSettingsDialog.h" 

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
    void showPageAccueil();
    void showPageGame();
    void showPageRegister();
    void showEcranJeu();
    void handleMusicSettingsChanged(bool musicEnabled, int volume);

private:
    QStackedWidget *stackedWidget;
    PageAccueil *pageAccueil;
    PageGame *pageGame;
    PageRegister *pageRegister;
    ecranJeu *pageEcranJeu;
    Joueur *joueur;

    void createActions();
    void createMenus();
    void openMusicSettingsDialog(); 

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QAction *saveAct;
    QAction *aboutAct;
    QAction *settingsAction;
    QLabel *infoLabel;
    QPushButton *buttonNouvellePartie;
    QPushButton *buttonChargerPartie;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *playlist;
    QAction *openMusicSettingsAct;
    MusicSettingsDialog *musicSettingsDialog;
};

#endif