#ifndef PAGEACCUEIL_H
#define PAGEACCUEIL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class PageAccueil : public QWidget
{
    Q_OBJECT

public:
    PageAccueil(QWidget *parent = nullptr);
    ~PageAccueil();

signals:
    void newGameButtonClicked();
    void continueGameButtonClicked();

private:
    QPushButton *buttonNouvellePartie;
    QPushButton *buttonChargerPartie;
    QVBoxLayout *mainLayout;
};

#endif // PAGEACCUEIL_H
