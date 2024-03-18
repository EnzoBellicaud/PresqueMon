#ifndef PAGEGAME_H
#define PAGEGAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QPushButton>
#include <QLabel>

class PageGame : public QWidget
{
    Q_OBJECT

public:
    PageGame(QWidget *parent = nullptr);
    ~PageGame();

public slots:
    void loadInfos();

signals:
    void playButtonClicked();

private:
    void updateDisplay(const QJsonObject &jsonObj);

    QVBoxLayout *layout;
    QLabel *infoPlayerLabel;
    QPushButton *playButton;
};

#endif // PAGEGAME_H
