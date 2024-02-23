#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include "../../Service/Service.h"

class UserWindow : public QWidget {
Q_OBJECT
private:
    Service* service;
    std::vector<TrenchCoat> coats;
    QSize buttonSize;

    QLabel* userSizeLabel;
    QLineEdit* userSizeText;

    QVBoxLayout* userSizeLayout;
    QFormLayout* userSizeForm;
    QPushButton* submitUserSizeButton;

    QWidget* userShoppingWidget;
    QVBoxLayout* userShoppingVLayout;
    QLabel* userShoppingCoatFields;
    QHBoxLayout* userButtonsLayout;

    QPushButton* addToCartButton;
    QPushButton* nextButton;
    QPushButton* exitShoppingButton;
    QPushButton* seeCoatButton;
    QPushButton* goToCartButton;

    QPushButton* showFileButton;

    int shoppingCoatIndex;

public:
    explicit UserWindow(Service* _service, QWidget* parent = nullptr);

    void runUserShopping();

public slots:

    void getCoatsBySize();

    void showCurrentCoatPhoto();

    void nextCoat();

    void shoppingCart();

    void addToCart();
};
