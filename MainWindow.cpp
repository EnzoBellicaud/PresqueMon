#include <QtWidgets>
#include <QPushButton>
#include <QStackedWidget>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setMedia(QUrl::fromLocalFile("data/musiqueCombat.mp3"));


    pageAccueil = new PageAccueil;
    pageRegister = new PageRegister;
    pageGame = new PageGame;
    pageEcranJeu = new ecranJeu;

    stackedWidget->addWidget(pageAccueil);
    stackedWidget->addWidget(pageGame);
    stackedWidget->addWidget(pageRegister);
    stackedWidget->addWidget(pageEcranJeu);

    connect(pageAccueil, &PageAccueil::newGameButtonClicked, this, &MainWindow::showPageRegister);
    connect(pageAccueil, &PageAccueil::continueGameButtonClicked, this, &MainWindow::showPageGame);
    connect(pageRegister, &PageRegister::backButtonClicked, this, &MainWindow::showPageAccueil);
    connect(pageRegister, &PageRegister::registeredEvent, this, &MainWindow::showPageGame);
    connect(pageGame, &PageGame::playButtonClicked, this, &MainWindow::showEcranJeu);
 
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
    if (musicSettingsDialog) {
        musicSettingsDialog->disconnect();
        delete musicSettingsDialog;
    }
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
            tr("The <b>Menu</b> example shows how to create "
               "menu-bar menus and context menus."));
}

void MainWindow::aboutQt()
{
    infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
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

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(settingsAction);
    
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::openMusicSettingsDialog()
{
    if (!musicSettingsDialog) {
        musicSettingsDialog = new MusicSettingsDialog(this);
        connect(musicSettingsDialog, &MusicSettingsDialog::musicSettingsChanged,
                this, &MainWindow::handleMusicSettingsChanged);
    }
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