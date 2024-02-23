#include "GUI.h"
#include "UI.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSize>
#include <QMainWindow>
#include "Components/MainMenu.h"

GUI::GUI(Service& _service, QWidget* parent) : QMainWindow(parent), UI(_service) {
    fileType = nullptr;
    buttonSize.setHeight(100);
    buttonSize.setWidth(100);
    mainWindow = new QWidget();
    mainLayout = new QVBoxLayout(mainWindow);
    fileTypeMenuWidget = new QWidget();
    fileTypeMenuWidget->hide();
    fileTypeLayout = new QVBoxLayout(fileTypeMenuWidget);
    HTML = new QPushButton("HTML");
    HTML->setMinimumSize(buttonSize);
    CSV = new QPushButton("CSV");
    CSV->setMinimumSize(buttonSize);
    auto askFileType = new QLabel("Which file type do you prefer?");
    askFileType->setMinimumSize(buttonSize);
    fileTypeLayout->addWidget(askFileType);
    fileTypeLayout->addWidget(HTML);
    fileTypeLayout->addWidget(CSV);
    backButton = new QPushButton("Back");
    backButton->setMinimumSize(buttonSize);
    backButton->hide();
    menu = new MainMenu();
    adminWindow = new AdminWindow(service);
    adminWindow->hide();

    userWindow = new UserWindow(service);
    userWindow->hide();

    mainLayout->addWidget(menu);
    mainLayout->addWidget(adminWindow);
    mainLayout->addWidget(fileTypeMenuWidget);
    mainLayout->addWidget(userWindow);
    mainLayout->addWidget(backButton);


    windows.push(menu);

    QObject::connect(menu->adminButton, &QPushButton::clicked, this, &GUI::runAdminWindow);
    QObject::connect(backButton, &QPushButton::clicked, this, &GUI::goBack);
    QObject::connect(menu->userButton, &QPushButton::clicked, this, &GUI::askFileType);
    QObject::connect(HTML, &QPushButton::clicked, this, &GUI::runUserWindowHTML);
    QObject::connect(CSV, &QPushButton::clicked, this, &GUI::runUserWindowCSV);
}

void GUI::startUI() {
    this->setCentralWidget(mainWindow);

    this->show();

    QApplication::exec();
}

void GUI::runAdminWindow() {
    getCurrentUsedWidget()->hide();

    adminWindow->show();
    backButton->show();
    windows.push(adminWindow);
}

QWidget* GUI::getCurrentUsedWidget() {
    return windows.top();
}

void GUI::goBack() {
    getCurrentUsedWidget()->hide();
    windows.pop();
    if (windows.size() == 1)
        backButton->hide();
    else
        backButton->show();
    getCurrentUsedWidget()->show();
}

void GUI::askFileType() {
    getCurrentUsedWidget()->hide();

    fileTypeMenuWidget->show();
    backButton->show();
    windows.push(fileTypeMenuWidget);
}

void GUI::runUserWindowHTML() {
    getCurrentUsedWidget()->hide();
    fileType = new CSVUserCoatList("../Data/coats.csv");
    service->setUserCoatList(fileType);

    userWindow->show();
}

void GUI::runUserWindowCSV() {
    getCurrentUsedWidget()->hide();

    fileType = new HTMLUserCoatList("../Data/coats.html");
    service->setUserCoatList(fileType);

    windows.push(userWindow);
    userWindow->show();

}

GUI::~GUI() = default;
