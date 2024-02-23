#pragma once

#include "../../Service/Service.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>

class AdminWindow : public QWidget{
    Q_OBJECT
private:
    Service* service;
    QSize buttonSize;
    QVBoxLayout* menuLayout;
    QPushButton* showCoatsButton;
    QPushButton* addCoatButton;
    QPushButton* removeCoatButton;
    QPushButton* updateCoatButton;

    QPushButton* submitAddCoatButton;
    QPushButton* submitRemoveCoatButton;
    QPushButton* submitUpdateCoatButton;

    QLabel* coatColorLabel;
    QLineEdit* coatColorText;
    QLabel* coatSizeLabel;
    QLineEdit* coatSizeText;
    QLabel* coatPriceLabel;
    QLineEdit* coatPriceText;
    QLabel* coatQuantityLabel;
    QLineEdit* coatQuantityText;
    QLabel* coatLinkLabel;
    QLineEdit* coatLinkText;
    QLabel* resultLabel;

    QLabel* coatColorToUpdateLabel;
    QLineEdit* coatColorToUpdateText;

    QVBoxLayout* addCoatLayout;
    QWidget* addCoatWidget;

    QVBoxLayout* removeCoatLayout;
    QWidget* removeCoatWidget;

    QVBoxLayout* updateCoatLayout;
    QWidget* updateCoatWidget;

public:
    explicit AdminWindow(Service* service, QWidget* parent = nullptr);

public slots:
    void showAllCoats();

    void addCoatMenu();

    void removeCoatMenu();

    void updateCoatMenu();

    void addCoat();

    void removeCoat();

    void updateCoat();
};
