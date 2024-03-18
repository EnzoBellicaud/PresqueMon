#include "Page2.h"
#include <QVBoxLayout>

Page2::Page2(QWidget *parent)
    : QWidget(parent)
{
    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &Page2::backButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(backButton);
    setLayout(layout);
}

Page2::~Page2()
{
}


