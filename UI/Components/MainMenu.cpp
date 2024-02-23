//
// Created by raul on 23.05.2023.
//

#include "MainMenu.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QTextBlock>
#include <QSize>
#include <QPalette>

MainMenu::MainMenu(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    adminButton = new QPushButton("Administrator");
    adminButton->setMinimumSize(100, 100);
    userButton = new QPushButton("User");
    userButton->setMinimumSize(100, 100);
    layout->addWidget(adminButton);
    layout->addWidget(userButton);
    this->setMinimumSize(500, 500);
}
