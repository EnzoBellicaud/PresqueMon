#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
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

QJsonArray Joueur::getInventory() const
{
    return m_inventory;
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

void Joueur::setInventory(const QJsonArray &inventory)
{
    m_inventory = inventory;
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


void Joueur::saveToJson(QString filename)
{
    // Créer un objet JSON
    QJsonObject json;
    json["pseudo"] = m_pseudo;
    json["lastSave"] = m_lastSave.toString(Qt::ISODate);
    json["money"] = m_money;
    QJsonArray pokemonArray;
    foreach(const Pokemon &pokemon, m_pokemon)
    {
        QJsonObject pokemonObject;
        pokemon.saveToJson(pokemonObject);
        pokemonArray.append(pokemonObject);
    }
    json["pokemon"] = pokemonArray;
    json["inventory"] = m_inventory;

    // Créer un document JSON à partir de l'objet JSON
    QJsonDocument jsonDocument(json);

    // Ouvrir le fichier en écriture
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Erreur lors de l'ouverture du fichier : " << file.errorString();
        return;
    }

    // Écrire le document JSON dans le fichier
    file.write(jsonDocument.toJson());

    // Vérification des erreurs d'écriture
    if (file.error() != QFile::NoError)
    {
        qDebug() << "Erreur lors de l'écriture dans le fichier : " << file.errorString();
        file.close();
        return;
    }

    // Fermeture du fichier
    file.close();
}

// Initialiser les données du joueur à partir d'un objet JSON
void Joueur::initializeFromJson(QJsonObject &json)
{
    m_pseudo = json["pseudo"].toString();
    m_money = json["money"].toInt();
    m_idPokemonFighting = json["idPokemonFighting"].toInt();

    QJsonArray pokemonArray = json["pokemon"].toArray();
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
