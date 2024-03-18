#include "PageRegister.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

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
    QString text = textField->text();
    QString filePath = "data/data.json";

    // Création du fichier JSON s'il n'existe pas
    if (!QFile::exists(filePath)) {
        QDir().mkpath("data");
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Impossible de créer le fichier : " << file.errorString();
            return;
        }
        file.write("{}"); // Crée un objet JSON vide
        file.close();
    }

    // Ouverture du fichier JSON en lecture/écriture
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier : " << file.errorString();
        return;
    }

    // Initialisation du champ "pseudo" avec la valeur de text
    QJsonObject obj;
    obj["pseudo"] = text;
    QJsonDocument save_doc(obj);
    
    // Ecriture du document JSON mis à jour dans le fichier
    file.resize(0); // Vide le contenu du fichier
    file.write(save_doc.toJson(QJsonDocument::Indented));

    // Vérification des erreurs d'écriture
    if (file.error() != QFile::NoError) {
        qDebug() << "Erreur lors de l'écriture dans le fichier : " << file.errorString();
        file.close();
        return;
    }

    // Fermeture du fichier
    file.close();

    // Émission du signal startGameEvent() si l'écriture a réussi
    textField->clear();
    emit startGameEvent();
}


