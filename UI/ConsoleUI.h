#pragma once

#include "../Service/Service.h"
#include "UI.h"

class ConsoleUI : public UI {
private:
    static const char EXIT[2];
public:
    ConsoleUI(Service& service);

    ~ConsoleUI() override;

    void startUI() override;

    static std::string readInput();

    bool isAdministrator();

    static bool boolFromYesNoInput();

    static void askAdministrator();

    void displayAdministratorMenu();

    static void displayUpdateSubmenu();

    void runAdministratorMenu(std::string& adminOption);

    void runUserMenu();

    static std::tuple<std::string, std::string, double, int, std::string> readAllCoatInformation();

    static void clearStandardBuffer();

    static std::string readCoatColor();

    static std::string readCoatSize();

    static std::string readCoatPhotoLink();

    static double readCoatPrice();

    static int readCoatQuantity();

    void runUpdateSubmenu(std::string& coatColorToUpdate);

    void displayUserMenu();

    static void displayCartOptions();

    static void displayUserShoppingOptions();

    static void displayCurrentCoat(const TrenchCoat& coat, int index);
};