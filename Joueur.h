#ifndef JOUEUR_H
#define JOUEUR_H

#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class Joueur
{
public:
    // Constructeur
    Joueur();

    // Getters
    QString getPseudo() const;
    QDateTime getLastSave() const;
    QJsonArray getPokemon() const;
    QJsonArray getInventory() const;
    int getMoney() const;

    // Setters
    void setPseudo(const QString &pseudo);
    void setLastSave(const QDateTime &lastSave);
    void setPokemon(const QJsonArray &pokemon);
    void setInventory(const QJsonArray &inventory);
    void setMoney(int money);

    // Fonction pour initialiser les données du joueur
    void initializeFromJson(const QJsonObject &json);

private:
    QString m_pseudo;
    QDateTime m_lastSave;
    QJsonArray m_pokemon;
    QJsonArray m_inventory;
    int m_money;
};

#endif // JOUEUR_H
