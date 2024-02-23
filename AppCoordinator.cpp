#include "Tests/TestTrenchCoat.h"
#include "Tests/TestRepository.h"
#include "Tests/TestService.h"
#include "UI/ConsoleUI.h"
#include "Exceptions/FileException.h"
#include <QApplication>
#include "UI/GUI.h"

class AppCoordinator {
private:
    Repository* repository;
    Service* service;
    UI* ui;
public:
    AppCoordinator() = default;

    ~AppCoordinator() {
        delete repository;
        delete service;
        delete ui;
    }

    void start() {
        this->initializeLayers();
        ui->startUI();
    }

private:
    void initializeLayers() {
        repository = new Repository("../Data/data.txt");
        service = new Service(*repository);
        ui = new GUI(*service);
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    AppCoordinator app = AppCoordinator();
    try{
        app.start();
    }
    catch (FileException& exception){
        std::cout << exception.what() << '\n';
    }
}