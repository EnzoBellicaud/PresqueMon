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
    QJsonObject obj = initializeJson();
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
    emit registeredEvent();
}

QJsonObject PageRegister::initializeJson()
{
    QJsonObject json;

    // Récupérer la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString dateTimeString = currentDateTime.toString(Qt::ISODate);

    // Initialiser les champs du JSON
    json["pseudo"] = textField->text();;
    json["lastSave"] = dateTimeString;

    // Initialiser la liste des Pokémon
    QJsonArray pokemonArray;
    QJsonObject pokemonObject;
    pokemonObject["id"] = 1;
    pokemonObject["name"] = "Bulbizarre";
    pokemonObject["type"] = "plante";
    pokemonObject["pv"] = 45;
    pokemonObject["pvMax"] = 45;
    pokemonObject["xp"] = 0;
    pokemonObject["level"] = 1;
    pokemonObject["attack"] = 49;
    pokemonObject["defense"] = 49;
    pokemonObject["speed"] = 45;
    pokemonObject["status"] = "normal";
    pokemonObject["imageDos"] = "data/bulbizarre_dos.png";
    pokemonObject["imageFace"] = "data/bulbizarre_face.png";
    pokemonArray.append(pokemonObject);
    json["pokemon"] = pokemonArray;

    // Initialiser l'inventaire (non implémenté dans le jeu pour l'instant, remplacé par le magasin)
    QJsonArray inventoryArray;
    QJsonObject inventoryObject;
    inventoryObject["id"] = 1;
    inventoryObject["name"] = "Potion";
    inventoryObject["quantity"] = 3;
    inventoryArray.append(inventoryObject);
    json["inventory"] = inventoryArray;

    // Initialiser l'argent
    json["money"] = 0;

    return json;
}
