#ifndef MAGASINWINDOW_H
#define MAGASINWINDOW_H

#include <QMainWindow>

class MagasinWindow : public QMainWindow
{
    Q_OBJECT

public:
    MagasinWindow(QWidget *parent = nullptr);
    ~MagasinWindow();

private slots:
    void acheterPotion();
    // Ajoutez d'autres slots pour les fonctionnalités du magasin

private:
    void setupUi();
};

#endif // MAGASINWINDOW_H
