#ifndef JOUEUR_H
#define JOUEUR_H

#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include "Pokemon.h"

class Joueur
{
public:
    // Constructeur
    Joueur();

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
    void setPseudo(const QString &pseudo);
    void setLastSave(const QDateTime &lastSave);
    void setPokemon(const QVector<Pokemon> &pokemon);
    void setIdPokemonFighting(int idPokemonFighting);
    void setInventory(const QJsonArray &inventory);
    void setMoney(int money);
    void setPokemonFighting(int idPokemonFighting);

    // Fonction pour initialiser les données du joueur
    void initializeFromJson(QJsonObject &json);
    void saveToJson(QString &filename);

private:
    QString m_pseudo;
    QDateTime m_lastSave;
    QVector<Pokemon> m_pokemon;
    QJsonArray m_inventory;
    int m_money;
    int m_idPokemonFighting;
};

#endif // JOUEUR_H
