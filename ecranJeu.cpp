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

int gamePlay (int argc, char *argv[ ])
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *ecranJeu;
    QHBoxLayout *zoneCombat;
    QVBoxLayout *monstreJoueur;
    QFrame *imageJoueur;
    QProgressBar *vieJoueur;
    QVBoxLayout *monstreAdversaire;
    QProgressBar *vieAdversaire;
    QFrame *imageAdversaire;
    QHBoxLayout *zoneChoix;
    QScrollArea *combatInfo;
    QWidget *combatInfoContent;
    QGridLayout *grilleOptions;
    QPushButton *boutonEquipe;
    QPushButton *boutonFuite;
    QPushButton *boutonAttaque;
    QPushButton *boutonSac;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        QApplication app(argc,argv);

        ecranJeu = new QVBoxLayout();
        ecranJeu->setContentsMargins(0, 0, 0, 0);

        //------------------------------- Zone Combat ---------------------------------

        zoneCombat = new QHBoxLayout();

        monstreJoueur = new QVBoxLayout();
        imageJoueur = new QFrame();
        vieJoueur = new QProgressBar();

        //imageJoueur->setFrameShape(QFrame::StyledPanel);
        //imageJoueur->setFrameShadow(QFrame::Raised);
        vieJoueur->setValue(100);

        monstreJoueur->addWidget(imageJoueur);
        monstreJoueur->addWidget(vieJoueur);

        zoneCombat->addLayout(monstreJoueur);
        

        monstreAdversaire = new QVBoxLayout();
        vieAdversaire = new QProgressBar();
        imageAdversaire = new QFrame();

        vieAdversaire->setValue(100);
        //imageAdversaire->setFrameShape(QFrame::StyledPanel);
        //imageAdversaire->setFrameShadow(QFrame::Raised);

        monstreAdversaire->addWidget(vieAdversaire);
        monstreAdversaire->addWidget(imageAdversaire);

        zoneCombat->addLayout(monstreAdversaire);
        
        
        //------------------------------- Zone Choix ---------------------------------

        zoneChoix = new QHBoxLayout();

        combatInfo = new QScrollArea();
        combatInfoContent = new QWidget();
        
        //combatInfo->setWidgetResizable(true);
        //combatInfoContent->setEnabled(true);
        combatInfoContent->setGeometry(QRect(0, 0, 531, 420));
        combatInfoContent->setMinimumSize(QSize(531, 0));
        combatInfo->setWidget(combatInfoContent);

        zoneChoix->addWidget(combatInfo);

        grilleOptions = new QGridLayout();
        boutonEquipe = new QPushButton();
        boutonFuite = new QPushButton();
        boutonAttaque = new QPushButton();
        boutonSac = new QPushButton();

        grilleOptions->addWidget(boutonEquipe, 1, 2, 1, 1);
        grilleOptions->addWidget(boutonFuite, 1, 0, 1, 1);
        grilleOptions->addWidget(boutonAttaque, 0, 0, 1, 1);
        grilleOptions->addWidget(boutonSac, 0, 2, 1, 1);

        zoneChoix->addLayout(grilleOptions);


        ecranJeu->addLayout(zoneCombat);
        ecranJeu->addLayout(zoneChoix);
        

        QWidget::setTabOrder(boutonAttaque, boutonSac);
        QWidget::setTabOrder(boutonSac, boutonFuite);
        QWidget::setTabOrder(boutonFuite, boutonEquipe);
        QWidget::setTabOrder(boutonEquipe, combatInfo);

        //retranslateUi(MainWindow);

        ecranJeu.show( );
	    return app.exec( );

        //QMetaObject::connectSlotsByName(MainWindow);
    }

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        boutonEquipe->setText(QCoreApplication::translate("MainWindow", "Equipe", nullptr));
        boutonFuite->setText(QCoreApplication::translate("MainWindow", "Fuite", nullptr));
        boutonAttaque->setText(QCoreApplication::translate("MainWindow", "Attaque", nullptr));
        boutonSac->setText(QCoreApplication::translate("MainWindow", "Sac", nullptr));
    } // retranslateUi

};