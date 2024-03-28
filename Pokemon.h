#ifndef POKEMON_H
#define POKEMON_H

#include <QString>
#include <QJsonObject>

class Pokemon {
private:
    int attack;
    int defense;
    int id;
    int level;
    QString name;
    int pv;
    int pvMax;
    int speed;
    QString status;
    QString type;
    int xp;
    QString imageDos;
    QString imageFace;

public:
    Pokemon();
    
    // Getters
    int getAttack() const;
    int getDefense() const;
    int getId() const;
    int getLevel() const;
    QString getName() const;
    int getPV() const;
    int getPVMax() const;
    int getSpeed() const;
    QString getStatus() const;
    QString getType() const;
    int getXp() const;
    QString getImageDos() const;
    QString getImageFace() const;

    // Setters
    void setAttack(int attack);
    void setDefense(int defense);
    void setId(int id);
    void setLevel(int level);
    void setName(const QString& name);
    void setPV(int pv);
    void setPVMax(int pvMax);
    void setSpeed(int speed);
    void setStatus(const QString& status);
    void setType(const QString& type);
    void setXp(int xp);
    void setImageDos(const QString& imageDos);
    void setImageFace(const QString& imageFace);

    void addPV(int pv);

    void initializeFromJson(QJsonObject &json);
    void saveToJson(QJsonObject &json) const;
};

#endif // POKEMON_H
