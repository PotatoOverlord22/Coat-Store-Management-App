#include "AdminWindow.h"
#include "../../Exceptions/RepositoryException.h"

AdminWindow::AdminWindow(Service* _service, QWidget* parent) : service(_service) {
    buttonSize.setWidth(100);
    buttonSize.setHeight(100);
    menuLayout = new QVBoxLayout(this);
    showCoatsButton = new QPushButton("Show all coats");
    addCoatButton = new QPushButton("Add coat");
    removeCoatButton = new QPushButton("Remove coat");
    updateCoatButton = new QPushButton("Update coat");
    showCoatsButton->setMinimumSize(buttonSize);
    addCoatButton->setMinimumSize(buttonSize);
    removeCoatButton->setMinimumSize(buttonSize);
    updateCoatButton->setMinimumSize(buttonSize);
    menuLayout->addWidget(showCoatsButton);
    menuLayout->addWidget(addCoatButton);
    menuLayout->addWidget(removeCoatButton);
    menuLayout->addWidget(updateCoatButton);

    connect(showCoatsButton, &QPushButton::clicked, this, &AdminWindow::showAllCoats);
    connect(addCoatButton, &QPushButton::clicked, this, &AdminWindow::addCoatMenu);
    connect(removeCoatButton, &QPushButton::clicked, this, &AdminWindow::removeCoatMenu);
    connect(updateCoatButton, &QPushButton::clicked, this, &AdminWindow::updateCoatMenu);

    submitAddCoatButton = new QPushButton("Add coat");
    submitAddCoatButton->setMinimumSize(buttonSize);

    submitRemoveCoatButton = new QPushButton("Remove coat");
    submitRemoveCoatButton->setMinimumSize(buttonSize);

    submitUpdateCoatButton = new QPushButton("Update coat");
    submitUpdateCoatButton->setMinimumSize(buttonSize);

    coatColorToUpdateLabel = new QLabel("Coat to update color: ");
    coatColorToUpdateText = new QLineEdit();
    coatColorToUpdateLabel->setBuddy(coatColorToUpdateText);

    coatColorLabel = new QLabel("Coat color: ");
    coatColorText = new QLineEdit();
    coatColorLabel->setBuddy(coatColorText);

    coatSizeLabel = new QLabel("Coat size: ");
    coatSizeText = new QLineEdit();
    coatSizeLabel->setBuddy(coatSizeText);

    coatPriceLabel = new QLabel("Coat price: ");
    coatPriceText = new QLineEdit();
    coatPriceLabel->setBuddy(coatPriceText);

    coatQuantityLabel = new QLabel("Coat quantity: ");
    coatQuantityText = new QLineEdit();
    coatQuantityLabel->setBuddy(coatQuantityText);

    coatLinkLabel = new QLabel("Coat photo link: ");
    coatLinkText = new QLineEdit();
    coatLinkLabel->setBuddy(coatLinkText);

    addCoatWidget = new QWidget();
    addCoatLayout = new QVBoxLayout(addCoatWidget);
    resultLabel = new QLabel();
    resultLabel->hide();

    removeCoatWidget = new QWidget();
    removeCoatLayout = new QVBoxLayout(removeCoatWidget);

    updateCoatWidget = new QWidget();
    updateCoatLayout = new QVBoxLayout(updateCoatWidget);

    connect(submitAddCoatButton, &QPushButton::clicked, this, &AdminWindow::addCoat);
    connect(submitRemoveCoatButton, &QPushButton::clicked, this, &AdminWindow::removeCoat);
    connect(submitUpdateCoatButton, &QPushButton::clicked, this, &AdminWindow::updateCoat);

}

void AdminWindow::showAllCoats() {
    auto showCoatsWidget = new QWidget();
    auto showCoatsLayout = new QVBoxLayout(showCoatsWidget);
    auto list = new QListWidget();
    showCoatsLayout->addWidget(list);
    auto& allCoats = service->getAllCoats();
    for (auto& coat: allCoats)
        list->addItem(QString::fromStdString(coat.toString()));

    showCoatsWidget->show();
}

void AdminWindow::addCoatMenu() {
    auto addCoatFieldsLayout = new QFormLayout();
    addCoatFieldsLayout->addRow(coatColorLabel, coatColorText);
    addCoatFieldsLayout->addRow(coatSizeLabel, coatSizeText);
    addCoatFieldsLayout->addRow(coatPriceLabel, coatPriceText);
    addCoatFieldsLayout->addRow(coatQuantityLabel, coatQuantityText);
    addCoatFieldsLayout->addRow(coatLinkLabel, coatLinkText);

    addCoatLayout->addLayout(addCoatFieldsLayout);
    addCoatLayout->addWidget(submitAddCoatButton);

    addCoatWidget->show();
}

void AdminWindow::removeCoatMenu() {
    auto removeCoatFieldsLayout = new QFormLayout();
    removeCoatFieldsLayout->addRow(coatColorLabel, coatColorText);

    removeCoatLayout->addLayout(removeCoatFieldsLayout);
    removeCoatLayout->addWidget(submitRemoveCoatButton);
    removeCoatWidget->show();
}

void AdminWindow::updateCoatMenu() {
    auto updateCoatFieldsLayout = new QFormLayout();
    updateCoatFieldsLayout->addRow(coatColorToUpdateLabel, coatColorToUpdateText);
    updateCoatFieldsLayout->addRow(coatColorLabel, coatColorText);
    updateCoatFieldsLayout->addRow(coatSizeLabel, coatSizeText);
    updateCoatFieldsLayout->addRow(coatPriceLabel, coatPriceText);
    updateCoatFieldsLayout->addRow(coatQuantityLabel, coatQuantityText);
    updateCoatFieldsLayout->addRow(coatLinkLabel, coatLinkText);

    updateCoatLayout->addLayout(updateCoatFieldsLayout);
    updateCoatLayout->addWidget(submitUpdateCoatButton);

    updateCoatWidget->show();
}

void AdminWindow::addCoat() {
    std::string color = coatColorText->text().toStdString();
    std::string size = coatSizeText->text().toStdString();
    double price = coatPriceText->text().toDouble();
    int quantity = coatQuantityText->text().toInt();
    std::string link = coatLinkText->text().toStdString();

    addCoatLayout->addWidget(resultLabel);
    resultLabel->clear();
    resultLabel->hide();
    try {
        service->addCoat(color, size, price, quantity, link);
        resultLabel->setText("Coat added successfully!");
        resultLabel->show();
    }
    catch (RepositoryException& repositoryException) {
        std::string msg1("Could not add coat: ");
        std::string msg2(repositoryException.what());
        resultLabel->setText(QString::fromStdString(msg1 + msg2));
        resultLabel->show();
    }
    coatColorText->clear();
    coatSizeText->clear();
    coatPriceText->clear();
    coatQuantityText->clear();
    coatLinkText->clear();
}

void AdminWindow::removeCoat() {
    std::string colorToRemove = coatColorText->text().toStdString();
    std::cout << "here";
    removeCoatLayout->addWidget(resultLabel);
    resultLabel->clear();
    resultLabel->hide();
    try {
        service->removeCoat(colorToRemove);
        std::cout << "removed";
        resultLabel->setText("Coat removed successfully!");
        resultLabel->show();
    }
    catch (RepositoryException& repositoryException) {
        std::cout << "not removed";
        std::string msg1("Could not remove coat: ");
        std::string msg2(repositoryException.what());
        resultLabel->setText(QString::fromStdString(msg1 + msg2));
        resultLabel->show();
    }
    coatColorText->clear();
}

void AdminWindow::updateCoat() {
    std::string coatColor = coatColorToUpdateText->text().toStdString();
    std::string color = coatColorText->text().toStdString();
    std::string size = coatSizeText->text().toStdString();
    double price = coatPriceText->text().toDouble();
    int quantity = coatQuantityText->text().toInt();
    std::string link = coatLinkText->text().toStdString();

    addCoatLayout->addWidget(resultLabel);
    resultLabel->clear();
    resultLabel->hide();
    try {
        service->updateAllCoatFields(coatColor, color, size, price, quantity, link);
        resultLabel->setText("Coat updated successfully!");
        resultLabel->show();
    }
    catch (RepositoryException& repositoryException) {
        std::string msg1("Could not update coat: ");
        std::string msg2(repositoryException.what());
        resultLabel->setText(QString::fromStdString(msg1 + msg2));
        resultLabel->show();
    }
    coatColorToUpdateText->clear();
    coatColorText->clear();
    coatSizeText->clear();
    coatPriceText->clear();
    coatQuantityText->clear();
    coatLinkText->clear();
}
