#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <iostream>
#include "Joueur.h"
#include "Pokemon.h"

// Constructeur
Joueur::Joueur()
{
}

// Getters
QString Joueur::getPseudo() const
{
    return m_pseudo;
}

QDateTime Joueur::getLastSave() const
{
    return m_lastSave;
}

QVector<Pokemon> Joueur::getPokemon() const {
    return m_pokemon;
}

int Joueur::getIdPokemonFighting() const {
    return m_idPokemonFighting;
}

int Joueur::getMoney() const
{
    return m_money;
}

Pokemon* Joueur::getFirstPokemon() {
    // parcourir la liste des pokemons et renvoie un pointeur vers le premier dont les pv sont supérieurs à 0
    for (int i = 0; i < m_pokemon.size(); i++) {
        if (m_pokemon[i].getPV() > 0) {
            m_idPokemonFighting = i;
            return &m_pokemon[i]; // Retourne un pointeur vers le Pokémon trouvé
        }
    }
    return &m_pokemon[0]; // Retourne un pointeur vers le premier Pokémon de la liste
}

Pokemon* Joueur::getPokemonFighting() {
    return &m_pokemon[m_idPokemonFighting]; // Retourne un pointeur vers le Pokémon en combat
}


// Setters
void Joueur::setPseudo(const QString &pseudo)
{
    m_pseudo = pseudo;
}

void Joueur::setLastSave(const QDateTime &lastSave)
{
    m_lastSave = lastSave;
}

void Joueur::setPokemon(const QVector<Pokemon> &pokemon)
{
    m_pokemon = pokemon;
}

void Joueur::setMoney(int money)
{
    m_money = money;
}

void Joueur::addMoney(int money)
{
    m_money += money;
}

void Joueur::setIdPokemonFighting(int idPokemonFighting){
    m_idPokemonFighting = idPokemonFighting;
}


void Joueur::saveToJson()
{
    QJsonObject json;
    json["pseudo"] = m_pseudo;
    json["lastSave"] = m_lastSave.toString(Qt::ISODate);
    json["money"] = m_money;
    json["idPokemonFighting"] = m_idPokemonFighting;
    // Récupérer la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString dateTimeString = currentDateTime.toString(Qt::ISODate);
    json["lastSave"] = dateTimeString;
    QJsonArray pokemonArray;
    foreach(const Pokemon &pokemon, m_pokemon)
    {
        QJsonObject pokemonObject;
        pokemon.saveToJson(pokemonObject);
        pokemonArray.append(pokemonObject);
    }
    json["pokemon"] = pokemonArray;

    QJsonDocument jsonDocument(json);
    QFile file("data/joueur.json");
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Erreur lors de l'ouverture du fichier : " << file.errorString();
        return;
    }
    file.write(jsonDocument.toJson());
    if (file.error() != QFile::NoError)
    {
        qDebug() << "Erreur lors de l'écriture dans le fichier : " << file.errorString();
        file.close();
        return;
    }
    file.close();
}

// Initialiser les données du joueur à partir d'un objet JSON
void Joueur::initializeFromJson()
{
    QFile file("data/joueur.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier.";
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError parseError; // Déclaration de QJsonParseError
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError); // Correction ici : jsonData au lieu de byteArray
    if (parseError.error != QJsonParseError::NoError) { // Vérifier si une erreur de parse est survenue
        qDebug() << "Erreur lors du parsing du JSON :" << parseError.errorString();
        return;
    }
    QJsonObject json  = jsonDoc.object();


    m_pseudo = json["pseudo"].toString();
    m_money = json["money"].toInt();
    m_idPokemonFighting = json["idPokemonFighting"].toInt();

    QJsonArray pokemonArray = json["pokemon"].toArray();
    m_pokemon.clear();
    foreach (const QJsonValue &pokemonValue, pokemonArray)
    {
        QJsonObject pokemonObject = pokemonValue.toObject();
        Pokemon pokemon;
        pokemon.initializeFromJson(pokemonObject);
        m_pokemon.append(pokemon);
    }
}


bool Joueur::finCombat()
{
    for (int i = 0; i < m_pokemon.size(); i++){
        if (m_pokemon[i].getPV() > 0){
            return false;
        }
    }
    return true;
}

void Joueur::initializeTestData(QString pseudo)
{
    QJsonObject json;

    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString dateTimeString = currentDateTime.toString(Qt::ISODate);

    json["lastSave"] = dateTimeString;

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
    json["idPokemonFighting"] = 0;
    json["money"] = 30;
    json["pseudo"] = pseudo;

    QString filePath = "data/joueur.json";
    if (!QFile::exists(filePath)) {
        QDir().mkpath("data");
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Impossible de créer le fichier : " << file.errorString();
            return;
        }
        file.write("{}"); 
        file.close();
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier : " << file.errorString();
        return;
    }
    QJsonObject obj = json;
    QJsonDocument save_doc(obj);
    file.resize(0); 
    file.write(save_doc.toJson(QJsonDocument::Indented));
    if (file.error() != QFile::NoError) {
        qDebug() << "Erreur lors de l'écriture dans le fichier : " << file.errorString();
        file.close();
        return;
    }
    file.close();
}
