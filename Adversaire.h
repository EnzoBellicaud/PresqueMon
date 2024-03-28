#ifndef ADVERSAIRE_H
#define ADVERSAIRE_H

#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>
#include "Pokemon.h"

class Adversaire
{
public:
    // Constructeur
    Adversaire();
    static void initializeTestData();

    // Getters
    QString getPseudo() const;
    QDateTime getLastSave() const;
    QVector<Pokemon> getPokemon() const;
    int getIdPokemonFighting() const;
    QJsonArray getInventory() const;
    int getMoney() const;

    Pokemon* getFirstPokemon();
    Pokemon* getPokemonFighting();
    bool finCombat();

    // Setters
    void setPokemon(const QVector<Pokemon> &pokemon);
    void setIdPokemonFighting(int idPokemonFighting);

    // Fonction pour initialiser les données du joueur
    void initializeFromJson();
    void saveToJson();

private:
    QString m_pseudo;
    QDateTime m_lastSave;
    QVector<Pokemon> m_pokemon;
    QJsonArray m_inventory;
    int m_idPokemonFighting;
};

#endif // ADVERSAIRE_H
