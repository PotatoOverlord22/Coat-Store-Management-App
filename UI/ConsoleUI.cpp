#include "ConsoleUI.h"
#include <iostream>
#include <limits>
#include <tuple>
#include <regex>
#include <map>
#include "../Exceptions/RepositoryException.h"
#include "../UserLists/FileUserCoatList.h"
#include "../UserLists/HTMLUserCoatList.h"
#include "../UserLists/CSVUserCoatList.h"
#include "UI.h"

const char ConsoleUI::EXIT[2] = "0";

ConsoleUI::ConsoleUI(Service& _service): UI(_service){
}

ConsoleUI::~ConsoleUI() = default;

void ConsoleUI::startUI() {
    /// Administrator
    if (isAdministrator()) {
        while (true) {
            displayAdministratorMenu();
            std::string userOption = readInput();
            if (userOption == EXIT)
                break;
            runAdministratorMenu(userOption);
        }
        /// User
    } else {
        displayUserMenu();
        const char SHOP[] = "1";
        std::string userOption = readInput();
        if (userOption == EXIT)
            return;
        if (userOption == SHOP) {
            runUserMenu();
        }
    }
}

void ConsoleUI::displayCartOptions() {
    std::cout << "\n1. Check-out / Open file";
    std::cout << "\t\t2. Continue shopping";
    std::cout << "\t\t0. Exit app";
}

void ConsoleUI::displayCurrentCoat(const TrenchCoat& coat, int index) {
    std::cout << "\nThis is coat " << index + 1 << ":\n";
    std::cout << coat.toString();
}

void ConsoleUI::displayUserShoppingOptions() {
    std::cout << "\n1. See coat photo";
    std::cout << "\t\t2. Add coat to cart";
    std::cout << "\t\t3. Next coat";
    std::cout << "\t\t4. Go to cart";
    std::cout << "\t\t0. Exit app";
}

void ConsoleUI::displayUserMenu() {
    std::cout << "\nMenu:";
    std::cout << "\n\t1. Start shopping";
    std::cout << "\n\t0. Exit";
}

void ConsoleUI::askAdministrator() {
    std::cout << "\nAdministrator mode? (Y/N)";
}

std::string ConsoleUI::readInput() {
    std::string input;
    std::cout << "\n > ";
    std::cin >> input;
    ConsoleUI::clearStandardBuffer();
    return input;
}

bool ConsoleUI::boolFromYesNoInput() {
    std::string userInput = readInput();
    for (char& i: userInput)
        i = (char) tolower(i);
    if (userInput == "yes")
        return true;
    if (userInput == "y")
        return true;
    if (userInput == "1")
        return true;
    return false;
}

bool ConsoleUI::isAdministrator() {
    this->askAdministrator();
    return boolFromYesNoInput();
}

void ConsoleUI::displayAdministratorMenu() {
    std::cout << "\nAdministrator Menu:";
    std::cout << "\n\t1. Display all coats";
    std::cout << "\n\t2. Add a new coat";
    std::cout << "\n\t3. Remove a coat";
    std::cout << "\n\t4. Update a coat";
    std::cout << "\n\t0. Exit";
}

void ConsoleUI::runAdministratorMenu(std::string& adminOption) {
    const char DISPLAY[2] = "1";
    const char ADD_NEW_COAT[2] = "2";
    const char REMOVE_COAT[2] = "3";
    const char UPDATE_COAT[2] = "4";
    /// Display coats
    if (adminOption == DISPLAY) {
        std::vector<TrenchCoat> allCoats = this->service->getAllCoats();
        for (auto& currentCoat: allCoats)
            std::cout << currentCoat.toString() << "\n";
    }
        /// Add coat
    else if (adminOption == ADD_NEW_COAT) {
        auto [color, size, price, quantity, photoLink] = ConsoleUI::readAllCoatInformation();
        try {
            service->addCoat(color, size, price, quantity, photoLink);
        }
        catch (RepositoryException& repositoryException) {
            std::cout << repositoryException.what() << '\n';
        }
    }
        /// Remove coat
    else if (adminOption == REMOVE_COAT) {
        std::string coatToRemoveColor = readCoatColor();
        try {
            service->removeCoat(coatToRemoveColor);
        }
        catch (RepositoryException& repositoryException) {
            std::cout << repositoryException.what() << '\n';
        }
    }
        /// Update coat
    else if (adminOption == UPDATE_COAT) {
        std::string coatToUpdateColor = readCoatColor();
        runUpdateSubmenu(coatToUpdateColor);
    }
}

void ConsoleUI::runUpdateSubmenu(std::string& coatColorToUpdate) {
    const char EXIT_SUBMENU[2] = "0";
    const char UPDATE_COLOR[2] = "1";
    const char UPDATE_SIZE[2] = "2";
    const char UPDATE_PRICE[2] = "3";
    const char UPDATE_QUANTITY[2] = "4";
    const char UPDATE_LINK[2] = "5";
    if (!service->findCoat(coatColorToUpdate)) {
        std::cout << "Coat does not exist.";
        return;
    } else {
        while (true) {
            displayUpdateSubmenu();
            TrenchCoat& coatToUpdate = service->getCoatByColor(coatColorToUpdate);
            std::string color = coatToUpdate.getColor();
            std::string size = coatToUpdate.getSize();
            double price = coatToUpdate.getPrice();
            int quantity = coatToUpdate.getQuantity();
            std::string photo = coatToUpdate.getPhotograph();

            std::string userUpdateChoice = readInput();
            if (userUpdateChoice == EXIT_SUBMENU)
                return;
                /// Update color
            else if (userUpdateChoice == UPDATE_COLOR) {
                color = readCoatColor();
            }
                /// Update size
            else if (userUpdateChoice == UPDATE_SIZE) {
                size = readCoatSize();
            }
                /// Update photo-image link of coat
            else if (userUpdateChoice == UPDATE_LINK) {
                photo = readCoatPhotoLink();

            }
                /// Update price
            else if (userUpdateChoice == UPDATE_PRICE) {
                price = readCoatPrice();

            }
                /// Update quantity
            else if (userUpdateChoice == UPDATE_QUANTITY) {
                quantity = readCoatQuantity();
            }
            try {
                service->updateAllCoatFields(coatColorToUpdate, color, size, price, quantity, photo);
                coatColorToUpdate = color;
                std::cout << "Coat updated successfully." << '\n';
            }
            catch (RepositoryException& repositoryException) {
                std::cout << repositoryException.what() << '\n';
            }
        }
    }
}

void ConsoleUI::displayUpdateSubmenu() {
    std::cout << "\n\tWhat field do you want to update?";
    std::cout << "\n\t\t1. Color";
    std::cout << "\n\t\t2. Size";
    std::cout << "\n\t\t3. Price";
    std::cout << "\n\t\t4. Quantity";
    std::cout << "\n\t\t5. Photo link";
    std::cout << "\n\t\t0. Exit submenu";
}

std::tuple<std::string, std::string, double, int, std::string> ConsoleUI::readAllCoatInformation() {
    std::string color, size, photoLink;
    double price;
    int quantity;
    color = readCoatColor();
    size = readCoatSize();
    price = readCoatPrice();
    quantity = readCoatQuantity();
    photoLink = readCoatPhotoLink();
    return {color, size, price, quantity, photoLink};
}

std::string ConsoleUI::readCoatColor() {
    std::string color;
    std::cout << "Coat color: ";
    std::getline(std::cin, color);
    return color;
}

std::string ConsoleUI::readCoatSize() {
    std::string size;
    std::cout << "Coat size: ";
    std::getline(std::cin, size);
    return size;
}

std::string ConsoleUI::readCoatPhotoLink() {
    std::string photoLink;
    std::cout << "Coat photograph link: ";
    std::getline(std::cin, photoLink);
    return photoLink;
}

double ConsoleUI::readCoatPrice() {
    double price;
    std::cout << "Coat price: ";
    std::cin >> price;
    ConsoleUI::clearStandardBuffer();
    return price;
}

int ConsoleUI::readCoatQuantity() {
    int quantity;
    std::cout << "Coat quantity: ";
    std::cin >> quantity;
    ConsoleUI::clearStandardBuffer();
    return quantity;
}

void ConsoleUI::clearStandardBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ConsoleUI::runUserMenu() {
    std::cout << "In what type of file would you like to store your shopping cart? (HTML/CSV)";
    std::string fileTypeStr = readInput();

    std::regex HTML("[Hh][Tt][Mm][Ll]");
    std::regex CSV("[Cc][Ss][Vv]");

    FileUserCoatList* fileType = nullptr;

    if (std::regex_match(fileTypeStr, HTML))
        fileType = new HTMLUserCoatList("../Data/coats.html");
    else if (std::regex_match(fileTypeStr, CSV))
        fileType = new CSVUserCoatList("../Data/coats.csv");

    if (fileType != nullptr)
        service->setUserCoatList(fileType);

    std::cout << "What is your size?\n";
    std::string filterSize = readCoatSize();
    std::vector<TrenchCoat> filteredCoats;
    this->service->putFilteredCoats(filteredCoats, filterSize);
    int coatIndex = 0;
    std::vector<TrenchCoat> cartCoats;
    double cartPrice = 0;

    while (true) {
        // display current coat
        TrenchCoat& currentCoat = filteredCoats[coatIndex];
        ConsoleUI::displayCurrentCoat(currentCoat, coatIndex);
        // display user options
        displayUserShoppingOptions();
        const char SEE_PHOTO[] = "1";
        const char ADD_TO_CART[] = "2";
        const char NEXT[] = "3";
        const char CART[] = "4";
        std::string userShopOption = readInput();
        /// Exit app
        if (userShopOption == EXIT) {
            delete fileType;
            return;
        }
            /// Launch photo in browser
        else if (userShopOption == SEE_PHOTO) {
            std::string openPhotoLink;
            openPhotoLink.append("xdg-open \"" + currentCoat.getPhotograph() + '"');
            if (system(openPhotoLink.c_str()) == 0)
                std::cout << "\nPhoto opened successfully.";
            else
                std::cout << "\nCould not open the photo.";
        }
            /// Add coat to cart
        else if (userShopOption == ADD_TO_CART) {
            if (currentCoat.getQuantity() <= 0)
                std::cout << "Out of stock!";
            else {
                cartPrice += currentCoat.getPrice();
                cartCoats.push_back(currentCoat);
                service->addCoatToUserList(currentCoat);
                currentCoat.setQuantity(currentCoat.getQuantity() - 1);
                std::cout << "Item added to cart successfully!";
            }
        }
            /// Next coat
        else if (userShopOption == NEXT) {
            if (coatIndex >= filteredCoats.size() - 1)
                coatIndex = 0;
            else
                coatIndex++;
            continue;
        }
            /// Go to cart section
        else if (userShopOption == CART) {
            while (true) {
                std::cout << "\nCart number of items: " << cartCoats.size();
                std::cout << "\nCart total price: $" << cartPrice;
                ConsoleUI::displayCartOptions();
                std::string userCartOption = readInput();
                const char CHECK_OUT[] = "1";
                const char CONTINUE_SHOPPING[] = "2";
                if (userCartOption == EXIT)
                    return;
                if (userCartOption == CHECK_OUT) {
                    service->openUserList();
//                    std::cout << "Thank you for shopping with us!";
//                    return;
                }
                if (userCartOption == CONTINUE_SHOPPING)
                    break;
            }
        }
    }
}

