#include <QtWidgets>
#include "mainwindow.h"

//https://code.qt.io/cgit/qt/qtbase.git/tree/examples/widgets/mainwindows/menus?h=6.6

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("Welcome to PresqueMon"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("PresqueMon"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(saveAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

//--------------------------------- début des fonctions ------------------------------

void MainWindow::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::musique()
{
    infoLabel->setText(tr("Invoked <b>File|Musique</b>"));
}

void MainWindow::sons()
{
    infoLabel->setText(tr("Invoked <b>File|Sons</b>"));
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

//--------------------------------- Fin des fonctions ------------------------------

void MainWindow::createActions()
{
    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the game"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    musiqueAct = new QAction(tr("&Musique"), this);
    musiqueAct->setCheckable(true);
    musiqueAct->setStatusTip(tr("Mettre la musique"));
    connect(musiqueAct, &QAction::triggered, this, &MainWindow::musique);

    sonsAct = new QAction(tr("&Sons"), this);
    sonsAct->setCheckable(true);
    sonsAct->setStatusTip(tr("Mettre les sons"));
    connect(sonsAct, &QAction::triggered, this, &MainWindow::sons);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    //fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(musiqueAct);
    editMenu->addAction(sonsAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
