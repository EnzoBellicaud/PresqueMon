#include <QtWidgets>
#include <QPushButton>
#include <QStackedWidget>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    pageAccueil = new PageAccueil;
    pageGame = new Page2;

    stackedWidget->addWidget(pageAccueil);
    stackedWidget->addWidget(pageGame);

    connect(pageAccueil, &PageAccueil::newGameButtonClicked, this, &MainWindow::showPageGame);
    connect(pageAccueil, &PageAccueil::continueGameButtonClicked, this, &MainWindow::showPageGame);
    connect(pageGame, &Page2::backButtonClicked, this, &MainWindow::showPageAccueil);
 
    infoLabel = new QLabel(tr("Welcome to PresqueMon"));
    infoLabel->setAlignment(Qt::AlignCenter);

    createActions();
    createMenus();

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
}

void MainWindow::showPageAccueil()
{
    stackedWidget->setCurrentWidget(pageAccueil); 
}

void MainWindow::showPageGame()
{
    stackedWidget->setCurrentWidget(pageGame); 
}

void MainWindow::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
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

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
    
}