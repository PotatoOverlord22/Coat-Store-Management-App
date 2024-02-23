#include "UserWindow.h"

UserWindow::UserWindow(Service* _service, QWidget* parent) : QWidget(parent), service(_service) {
    shoppingCoatIndex = 0;
    buttonSize.setHeight(100);
    buttonSize.setWidth(100);

    userSizeLayout = new QVBoxLayout(this);
    userSizeForm = new QFormLayout();
    userSizeLayout->addLayout(userSizeForm);

    userSizeLabel = new QLabel("Please enter your size: ");
    userSizeText = new QLineEdit();
    userSizeLabel->setBuddy(userSizeText);

    userSizeForm->addRow(userSizeLabel, userSizeText);

    submitUserSizeButton = new QPushButton("Submit size");
    submitUserSizeButton->setMinimumSize(buttonSize);
    userSizeLayout->addWidget(submitUserSizeButton);

    connect(submitUserSizeButton, &QPushButton::clicked, this, &UserWindow::getCoatsBySize);

    userShoppingWidget = new QWidget();
    userShoppingVLayout = new QVBoxLayout(userShoppingWidget);
    userShoppingCoatFields = new QLabel();
    userButtonsLayout = new QHBoxLayout();
    userShoppingVLayout->addWidget(userShoppingCoatFields);
    userShoppingVLayout->addLayout(userButtonsLayout);

    addToCartButton = new QPushButton("Add coat to cart");
    nextButton = new QPushButton("Next coat");
    seeCoatButton = new QPushButton("Coat photo");
    goToCartButton = new QPushButton("Go to cart");
    exitShoppingButton = new QPushButton("Exit Shopping");

    userButtonsLayout->addWidget(addToCartButton);
    userButtonsLayout->addWidget(nextButton);
    userButtonsLayout->addWidget(seeCoatButton);
    userButtonsLayout->addWidget(goToCartButton);
    userButtonsLayout->addWidget(exitShoppingButton);

    showFileButton = new QPushButton("Show the shopping cart in file");

    connect(seeCoatButton, &QPushButton::clicked, this, &UserWindow::showCurrentCoatPhoto);
    connect(nextButton, &QPushButton::clicked, this, &UserWindow::nextCoat);
    connect(goToCartButton, &QPushButton::clicked, this, &UserWindow::shoppingCart);
    connect(addToCartButton, &QPushButton::clicked, this, &UserWindow::addToCart);
}

void UserWindow::getCoatsBySize() {
    std::string size = userSizeText->text().toStdString();

    coats.clear();
    service->putFilteredCoats(coats, size);

    runUserShopping();
}

void UserWindow::runUserShopping() {
    TrenchCoat currentCoat = coats[shoppingCoatIndex];

    userShoppingCoatFields->setText(QString::fromStdString(currentCoat.toString()));


    userShoppingWidget->show();
}

void UserWindow::showCurrentCoatPhoto() {
    TrenchCoat currentCoat = coats[shoppingCoatIndex];
    std::string openPhotoLink;
    openPhotoLink.append("xdg-open \"" + currentCoat.getPhotograph() + '"');
    if (system(openPhotoLink.c_str()) == 0)
        std::cout << "\nPhoto opened successfully.";
    else
        std::cout << "\nCould not open the photo.";
}

void UserWindow::nextCoat() {
    shoppingCoatIndex++;
    if (shoppingCoatIndex >= coats.size() - 1)
        shoppingCoatIndex = 0;
    TrenchCoat currentCoat = coats[shoppingCoatIndex];
    userShoppingCoatFields->setText(QString::fromStdString(currentCoat.toString()));
}

void UserWindow::shoppingCart() {
    service->openUserList();
}

void UserWindow::addToCart() {
    TrenchCoat currentCoat = coats[shoppingCoatIndex];
    service->addCoatToUserList(currentCoat);
}


