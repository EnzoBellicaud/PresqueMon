#ifndef PAGE2_H
#define PAGE2_H

#include <QWidget>
#include <QPushButton>

class Page2 : public QWidget
{
    Q_OBJECT

public:
    Page2(QWidget *parent = nullptr);
    ~Page2();

signals:
    void backButtonClicked();

private:
    QPushButton *backButton;
};

#endif // PAGE2_H
