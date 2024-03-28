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
    void registeredEvent();

private slots:
    void onValidateButtonClicked();

private:
    QPushButton *backButton;
    QLineEdit *textField;
    QPushButton *validateButton;
    void initializeJoueurJson();
    void initializeEnnemyJson();

};

#endif // PAGEREGISTER_H
