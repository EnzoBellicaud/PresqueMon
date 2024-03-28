#commentaire
TEMPLATE = app
TARGET = main
QT = core gui widgets multimedia
SOURCES += main.cpp \
    MainWindow.cpp \
    MusicSettingsDialog.cpp \
    PageAccueil.cpp \
    PageGame.cpp \
    PageRegister.cpp \
    ecranJeu.cpp \
    Joueur.cpp \
    Adversaire.cpp \
    Pokemon.cpp \
    EquipeWindow.cpp \
    MagasinWindow.cpp
HEADERS += \
    MainWindow.h \
    MusicSettingsDialog.h \
    PageAccueil.h \
    PageGame.h \
    PageRegister.h \
    ecranJeu.h \
    Joueur.h \
    Adversaire.h \
    Pokemon.h \
    EquipeWindow.h \
    MagasinWindow.h
DESTDIR = release
OBJECTS_DIR = tmp
MOC_DIR = tmp 
