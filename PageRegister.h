#ifndef PAGEREGISTER_H
#define PAGEREGISTER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

class PageRegister : public QWidget
{
    Q_OBJECT

public:
    PageRegister(QWidget *parent = nullptr);
    ~PageRegister();

signals:
    void backButtonClicked();
    void startGameEvent();

private slots:
    void onValidateButtonClicked();

private:
    QPushButton *backButton;
    QLineEdit *textField;
    QPushButton *validateButton;
};

#endif // PAGEREGISTER_H
