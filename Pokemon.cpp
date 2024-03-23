#include "Pokemon.h"
#include <QJsonObject>

Pokemon::Pokemon()
{
}

// Getter et Setter pour l'attribut "attack"
int Pokemon::getAttack() const {
    return attack;
}

void Pokemon::setAttack(int value) {
    attack = value;
}

// Getter et Setter pour l'attribut "defense"
int Pokemon::getDefense() const {
    return defense;
}

void Pokemon::setDefense(int value) {
    defense = value;
}

// Getter et Setter pour l'attribut "id"
int Pokemon::getId() const {
    return id;
}

void Pokemon::setId(int value) {
    id = value;
}

// Getter et Setter pour l'attribut "level"
int Pokemon::getLevel() const {
    return level;
}

void Pokemon::setLevel(int value) {
    level = value;
}

// Getter et Setter pour l'attribut "name"
QString Pokemon::getName() const {
    return name;
}

void Pokemon::setName(const QString &value) {
    name = value;
}

// Getter et Setter pour l'attribut "pv"
int Pokemon::getPV() const {
    return pv;
}

void Pokemon::setPV(int value) {
    pv = value;
}

// Getter et Setter pour l'attribut "pvMax"
int Pokemon::getPVMax() const {
    return pvMax;
}

void Pokemon::setPVMax(int value) {
    pvMax = value;
}

// Getter et Setter pour l'attribut "speed"
int Pokemon::getSpeed() const {
    return speed;
}

void Pokemon::setSpeed(int value) {
    speed = value;
}

// Getter et Setter pour l'attribut "status"
QString Pokemon::getStatus() const {
    return status;
}

void Pokemon::setStatus(const QString &value) {
    status = value;
}

// Getter et Setter pour l'attribut "type"
QString Pokemon::getType() const {
    return type;
}

void Pokemon::setType(const QString &value) {
    type = value;
}

// Getter et Setter pour l'attribut "xp"
int Pokemon::getXp() const {
    return xp;
}

void Pokemon::setXp(int value) {
    xp = value;
}

// Getter et Setter pour l'attribut "imageDos"

QString Pokemon::getImageDos() const {
    return imageDos;
}

void Pokemon::setImageDos(const QString &imageDos) {
    this->imageDos = imageDos;
}

// Getter et Setter pour l'attribut "imageFace"

QString Pokemon::getImageFace() const {
    return imageFace;
}

void Pokemon::setImageFace(const QString &imageFace) {
    this->imageFace = imageFace;
}

void Pokemon::addPV(int value)
{
    pv += value;
    if (pv > pvMax) {
        pv = pvMax;
    } else if (pv < 0) {
        pv = 0;
    }
}

void Pokemon::initializeFromJson(QJsonObject &json)
{
    setAttack(json["attack"].toInt());
    setDefense(json["defense"].toInt());
    setId(json["id"].toInt());
    setLevel(json["level"].toInt());
    setName(json["name"].toString());
    setPV(json["pv"].toInt());
    setPVMax(json["pvMax"].toInt());
    setSpeed(json["speed"].toInt());
    setStatus(json["status"].toString());
    setType(json["type"].toString());
    setXp(json["xp"].toInt());
    setImageDos(json["imageDos"].toString());
    setImageFace(json["imageFace"].toString());
}

void Pokemon::saveToJson(QJsonObject &json) const {
    json["attack"] = getAttack();
    json["defense"] = getDefense();
    json["id"] = getId();
    json["level"] = getLevel();
    json["name"] = getName();
    json["pv"] = getPV();
    json["pvMax"] = getPVMax();
    json["speed"] = getSpeed();
    json["status"] = getStatus();
    json["type"] = getType();
    json["xp"] = getXp();
    json["imageDos"] = getImageDos();
    json["imageFace"] = getImageFace();
}