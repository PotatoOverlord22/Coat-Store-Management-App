#pragma once

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include "Components/MainMenu.h"
#include "Components/AdminWindow.h"
#include "Components/UserWindow.h"
#include "../Service/Service.h"
#include "UI.h"
#include <stack>
#include "../UserLists/HTMLUserCoatList.h"
#include "../UserLists/CSVUserCoatList.h"


class GUI : public QMainWindow, public UI {
Q_OBJECT
private:
    QSize buttonSize;
    MainMenu* menu;
    AdminWindow* adminWindow;
    UserWindow* userWindow;
    QVBoxLayout* mainLayout;
    QPushButton* backButton;
    QWidget* mainWindow;
    std::stack<QWidget*> windows;
    FileUserCoatList* fileType;
    QWidget* fileTypeMenuWidget;
    QPushButton* HTML;
    QPushButton* CSV;
    QVBoxLayout* fileTypeLayout;

public:
    explicit GUI(Service& _service, QWidget* parent = nullptr);

    void startUI() override;

    ~GUI() override;

    QWidget* getCurrentUsedWidget();

public slots:

    void runAdminWindow();

    void goBack();

    void askFileType();

    void runUserWindowHTML();

    void runUserWindowCSV();
};