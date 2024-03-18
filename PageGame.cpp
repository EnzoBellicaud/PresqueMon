#include "PageGame.h"
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

PageGame::PageGame(QWidget *parent)
    : QWidget(parent)
{
    infoPlayerLabel = new QLabel(tr("Welcome"));
    infoPlayerLabel->setAlignment(Qt::AlignCenter); // Correction ici : infoPlayerLabel au lieu de infoPLayerLabel
    
    playButton = new QPushButton("Jouer", this); // Correction ici : playButton au lieu de playbutton

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(infoPlayerLabel);
    mainLayout->addWidget(playButton);
    setLayout(mainLayout);

    connect(playButton, &QPushButton::clicked, this, &PageGame::playButtonClicked);
}

PageGame::~PageGame()
{
}

void PageGame::loadInfos() // Correction ici : loadInfos au lieu de loadObjects
{
    QString filePath = "data/data.json";
    QFile file(filePath);
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
    
    QJsonObject jsonObj  = jsonDoc.object();

    updateDisplay(jsonObj);
}


void PageGame::updateDisplay(const QJsonObject &jsonObj)
{
    QJsonValue jsonVal;
    QTextStream textStream(stdout);

    jsonVal = jsonObj.value("pseudo");
    infoPlayerLabel->setText(tr("Welcome ")+ jsonVal.toString());
}
