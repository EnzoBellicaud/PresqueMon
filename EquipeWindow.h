#ifndef EQUIPEWINDOW_H
#define EQUIPEWINDOW_H

#include <QMainWindow>

class EquipeWindow : public QMainWindow
{
    Q_OBJECT

public:
    EquipeWindow(QWidget *parent = nullptr);
    ~EquipeWindow();

private slots:
    void changerPokemon();
    // Ajoutez d'autres slots pour les fonctionnalités de l'équipe

private:
    void setupUi();
};

#endif // EQUIPEWINDOW_H
