#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class MainMenu : public QWidget{
    Q_OBJECT

public:
    QPushButton* adminButton;
    QPushButton* userButton;

private:
    QVBoxLayout* layout;

public:
    explicit MainMenu(QWidget* parent = nullptr);

};

