#include "PageRegister.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QString>
#include "Joueur.h"
#include "Adversaire.h"


PageRegister::PageRegister(QWidget *parent)
    : QWidget(parent)
{
    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &PageRegister::backButtonClicked);

    textField = new QLineEdit(this);

    validateButton = new QPushButton("Valider", this); // Correction ici : Valider avec une majuscule
    connect(validateButton, &QPushButton::clicked, this, &PageRegister::onValidateButtonClicked); // Correction ici : onValidateButtonClicked

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(backButton);
    layout->addWidget(textField); // Ajout du champ texte au layout
    layout->addWidget(validateButton); // Ajout du bouton "Valider" au layout
    setLayout(layout);
}

PageRegister::~PageRegister()
{
}

void PageRegister::onValidateButtonClicked()
{
    Joueur::initializeTestData(textField->text());
    Adversaire::initializeTestData();
    
    textField->clear();
    emit registeredEvent();
}

