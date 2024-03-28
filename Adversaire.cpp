#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include "Adversaire.h"
#include "Pokemon.h"

// Constructeur
Adversaire::Adversaire()
{
}


QVector<Pokemon> Adversaire::getPokemon() const {
    return m_pokemon;
}

int Adversaire::getIdPokemonFighting() const {
    return m_idPokemonFighting;
}

Pokemon* Adversaire::getFirstPokemon() {
    // parcourir la liste des pokemons et renvoie un pointeur vers le premier dont les pv sont supérieurs à 0
    for (int i = 0; i < m_pokemon.size(); i++) {
        if (m_pokemon[i].getPV() > 0) {
            m_idPokemonFighting = i;
            return &m_pokemon[i]; // Retourne un pointeur vers le Pokémon trouvé
        }
    }
    return &m_pokemon[0]; // Retourne un pointeur vers le premier Pokémon de la liste
}

Pokemon* Adversaire::getPokemonFighting() {
    return &m_pokemon[m_idPokemonFighting]; // Retourne un pointeur vers le Pokémon en combat
}

void Adversaire::setPokemon(const QVector<Pokemon> &pokemon)
{
    m_pokemon = pokemon;
}

void Adversaire::setIdPokemonFighting(int idPokemonFighting){
    m_idPokemonFighting = idPokemonFighting;
}


void Adversaire::saveToJson()
{
    QJsonObject json;
    QJsonArray pokemonArray;
    foreach(const Pokemon &pokemon, m_pokemon)
    {
        QJsonObject pokemonObject;
        pokemon.saveToJson(pokemonObject);
        pokemonArray.append(pokemonObject);
    }
    json["pokemons"] = pokemonArray;
    json["idPokemonFighting"] = m_idPokemonFighting;
    QJsonDocument jsonDocument(json);
    QFile file("data/ennemy.json");
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
void Adversaire::initializeFromJson()
{
    QFile file("data/ennemy.json");
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
    m_idPokemonFighting = json["idPokemonFighting"].toInt();

    QJsonArray pokemonArray = json["pokemons"].toArray();
    m_pokemon.clear();
    foreach (const QJsonValue &pokemonValue, pokemonArray)
    {
        QJsonObject pokemonObject = pokemonValue.toObject();
        Pokemon pokemon;
        pokemon.initializeFromJson(pokemonObject);
        m_pokemon.append(pokemon);
    }
}

bool Adversaire::finCombat()
{
    for (int i = 0; i < m_pokemon.size(); i++){
        if (m_pokemon[i].getPV() > 0){
            return false;
        }
    }
    return true;
}

void Adversaire::initializeTestData() {
    QJsonObject json;

    // Initialiser les données de l'ennemi
    QJsonArray ennemiesArray;
    QJsonObject ennemyObject;
    ennemyObject["id"] = 1;
    ennemyObject["name"] = "Salamèche";
    ennemyObject["type"] = "feu";
    ennemyObject["pv"] = 39;
    ennemyObject["pvMax"] = 39;
    ennemyObject["xp"] = 0;
    ennemyObject["level"] = 1;
    ennemyObject["attack"] = 52;
    ennemyObject["defense"] = 43;
    ennemyObject["speed"] = 65;
    ennemyObject["status"] = "normal";
    ennemyObject["imageDos"] = "data/salameche_dos.png";
    ennemyObject["imageFace"] = "data/salameche_face.png";
    ennemiesArray.append(ennemyObject);

    ennemyObject["id"] = 1;
    ennemyObject["name"] = "Bulbizarre";
    ennemyObject["type"] = "plante";
    ennemyObject["pv"] = 45;
    ennemyObject["pvMax"] = 45;
    ennemyObject["xp"] = 0;
    ennemyObject["level"] = 1;
    ennemyObject["attack"] = 49;
    ennemyObject["defense"] = 49;
    ennemyObject["speed"] = 45;
    ennemyObject["status"] = "normal";
    ennemyObject["imageDos"] = "data/bulbizarre_dos.png";
    ennemyObject["imageFace"] = "data/bulbizarre_face.png";
    ennemiesArray.append(ennemyObject);
    json["pokemons"] = ennemiesArray;
    json["idPokemonFighting"] = 0;

    QString filePath = "data/ennemy.json";

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
    QJsonObject obj = json;
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
}