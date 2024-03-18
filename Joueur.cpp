#include "Joueur.h"

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

QJsonArray Joueur::getPokemon() const
{
    return m_pokemon;
}

QJsonArray Joueur::getInventory() const
{
    return m_inventory;
}

int Joueur::getMoney() const
{
    return m_money;
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

void Joueur::setPokemon(const QJsonArray &pokemon)
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

// Initialiser les données du joueur à partir d'un objet JSON
void Joueur::initializeFromJson(const QJsonObject &json)
{
    m_pseudo = json["pseudo"].toString();
    m_lastSave = QDateTime::fromString(json["lastSave"].toString(), Qt::ISODate);
    m_pokemon = json["pokemon"].toArray();
    m_inventory = json["inventory"].toArray();
    m_money = json["money"].toInt();
}
