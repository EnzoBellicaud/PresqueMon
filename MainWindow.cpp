#include <QtWidgets>
#include <QPushButton>
#include <QStackedWidget>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    playlist = new QMediaPlaylist(this); 
    playlist->addMedia(QUrl::fromLocalFile("data/musiqueCombat.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setPlaylist(playlist);

    pageAccueil = new PageAccueil;
    pageRegister = new PageRegister;
    pageGame = new PageGame;
    pageEcranJeu = new ecranJeu;
    musicSettingsDialog = new MusicSettingsDialog(this);

    stackedWidget->addWidget(pageAccueil);
    stackedWidget->addWidget(pageGame);
    stackedWidget->addWidget(pageRegister);
    stackedWidget->addWidget(pageEcranJeu);

    connect(pageAccueil, &PageAccueil::newGameButtonClicked, this, &MainWindow::showPageRegister);
    connect(pageAccueil, &PageAccueil::continueGameButtonClicked, this, &MainWindow::showPageGame);
    connect(pageRegister, &PageRegister::backButtonClicked, this, &MainWindow::showPageAccueil);
    connect(pageRegister, &PageRegister::registeredEvent, this, &MainWindow::showPageGame);
    connect(pageGame, &PageGame::playButtonClicked, this, &MainWindow::showEcranJeu);
    connect(musicSettingsDialog, &MusicSettingsDialog::musicSettingsChanged,this, &MainWindow::handleMusicSettingsChanged);
    connect(pageEcranJeu, &ecranJeu::resetGameClicked, this, &MainWindow::showPageRegister);

    infoLabel = new QLabel(tr("Welcome to PresqueMon"));
    infoLabel->setAlignment(Qt::AlignCenter);
    createActions();
    createMenus();

    //mediaPlayer.setMedia(QUrl("data/musiqueCombat.mp3"));
    setWindowTitle(tr("PresqueMon"));
    setMinimumSize(160, 160);
    resize(480, 320);
    showPageAccueil();
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(saveAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

MainWindow::~MainWindow()
{
    delete pageAccueil;
    delete pageGame;
    delete pageRegister;
    delete pageEcranJeu;
}

void MainWindow::showPageAccueil()
{
    stackedWidget->setCurrentWidget(pageAccueil); 
}

void MainWindow::showPageGame()
{
    pageGame->loadInfos();
    stackedWidget->setCurrentWidget(pageGame);
}

void MainWindow::showPageRegister()
{
    stackedWidget->setCurrentWidget(pageRegister); 
}

void MainWindow::showEcranJeu()
{
    pageEcranJeu->setupGamePlay();
    pageEcranJeu->setupUi();
    stackedWidget->setCurrentWidget(pageEcranJeu);
}

void MainWindow::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
    pageEcranJeu->saveGame();
}


void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("Bienvenue sur PresqueMon, un jeu de combat de monstres."
               "Cliquez sur le bouton 'Nouvelle Partie' pour commencer une nouvelle partie."));
}

void MainWindow::createActions()
{

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    settingsAction = new QAction(tr("Music Settings"), this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::openMusicSettingsDialog);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(settingsAction);
    
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::openMusicSettingsDialog()
{   
    musicSettingsDialog->exec();
}

void MainWindow::handleMusicSettingsChanged(bool musicEnabled, int volume)
{
    if (musicEnabled) {
        mediaPlayer->play();
    } else {
        mediaPlayer->stop();
    }
    mediaPlayer->setVolume(volume);

}