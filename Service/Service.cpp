#include "Service.h"
#include "../Exceptions/NotFoundException.h"
#include "../Exceptions/TrenchCoatException.h"
#include "../Exceptions/RepositoryException.h"
#include <algorithm>

Service::Service(Repository& repository) {
    this->repository = &repository;
}

Service::~Service() = default;

std::vector<TrenchCoat>& Service::getAllCoats() const {
    return repository->getAll();
}

void Service::addCoat(std::string& color, const std::string& size, const double price, const int quantity,
                      std::string& photo) {
    TrenchCoat newCoat{color, size, price, quantity, photo};
    try{
        coatValidator.validate(newCoat);
    }
    catch (TrenchCoatException& exception){
        throw RepositoryException(exception.what());
    }

    if (findCoat(color))
        throw RepositoryException("Coat already exists!");

    repository->addCoat(newCoat);
}


void Service::removeCoat(const std::string& color) const {
    int index = getCoatIndex(color);
    if (index == -1)
        throw RepositoryException("Coat does not exist!");

    repository->removeCoatByIndex(index);
}

bool Service::findCoat(const std::string& color) const {
    std::vector<TrenchCoat>& allCoats = this->repository->getAll();
    auto iterator = std::find_if(allCoats.begin(), allCoats.end(), [&color](TrenchCoat& coat) {
        return coat.getColor() == color;
    });
    if (iterator == allCoats.end())
        return false;
    return true;
}

int Service::getCoatIndex(const std::string& color) const{
    std::vector<TrenchCoat>& allCoats = this->getAllCoats();
    auto iterator = std::find_if(allCoats.begin(), allCoats.end(), [&color](TrenchCoat& coat) {
        return coat.getColor() == color;
    });
    // check if there exists a coat with that color
    if (iterator == allCoats.end()) {
        return -1;
    }
    return std::distance(allCoats.begin(), iterator);
}

void Service::updateAllCoatFields(const std::string& coatToUpdateColor, const std::string& newColor,
                                  const std::string& newSize, double newPrice, int newQuantity,
                                  const std::string& newPhoto) const {

    try {
        TrenchCoat validationCoat{newColor, newSize, newPrice, newQuantity, newPhoto};
        coatValidator.validate(validationCoat);

        TrenchCoat& coat = getCoatByColor(coatToUpdateColor);
        coat.setColor(newColor);
        coat.setSize(newSize);
        coat.setPrice(newPrice);
        coat.setQuantity(newQuantity);
        coat.setPhotograph(newPhoto);

        repository->updateFile();
    }
    catch (NotFoundException& notFound) {
        throw RepositoryException(notFound.what());
    }
    catch (TrenchCoatException& coatError) {
        throw RepositoryException(coatError.what());
    }
}

void Service::updateCoatColor(const std::string& coatToUpdateColor, const std::string& newColor) const {
    try {
        TrenchCoat& coat = getCoatByColor(coatToUpdateColor);
        coat.setColor(newColor);
        coatValidator.validate(coat);
        repository->updateFile();
    }
    catch (NotFoundException& notFound) {
        throw RepositoryException(notFound.what());
    }
    catch (TrenchCoatException& coatError) {
        throw RepositoryException(coatError.what());
    }
}

void Service::updateCoatSize(const std::string& coatToUpdateColor, const std::string& newSize) const {
    try {
        TrenchCoat& coat = getCoatByColor(coatToUpdateColor);
        coat.setSize(newSize);
        coatValidator.validate(coat);
        repository->updateFile();
    }
    catch (NotFoundException& notFound) {
        throw RepositoryException(notFound.what());
    }
    catch (TrenchCoatException& coatError) {
        throw RepositoryException(coatError.what());
    }
}

void Service::updateCoatPhotoLink(const std::string& coatToUpdateColor, const std::string& newLink) const {
    try {
        TrenchCoat& coat = getCoatByColor(coatToUpdateColor);
        coat.setPhotograph(newLink);
        coatValidator.validate(coat);
        repository->updateFile();
    }
    catch (NotFoundException& notFound) {
        throw RepositoryException(notFound.what());
    }
    catch (TrenchCoatException& coatError) {
        throw RepositoryException(coatError.what());
    }
}

void Service::updateCoatPrice(const std::string& coatToUpdateColor, const double newPrice) const {
    try {
        TrenchCoat& coat = getCoatByColor(coatToUpdateColor);
        coat.setPrice(newPrice);
        coatValidator.validate(coat);
        repository->updateFile();
    }
    catch (NotFoundException& notFound) {
        throw RepositoryException(notFound.what());
    }
    catch (TrenchCoatException& coatError) {
        throw RepositoryException(coatError.what());
    }
}

void Service::updateCoatQuantity(const std::string& coatToUpdateColor, const int newQuantity) const {
    try {
        TrenchCoat& coat = getCoatByColor(coatToUpdateColor);
        coat.setQuantity(newQuantity);
        coatValidator.validate(coat);
        repository->updateFile();
    }
    catch (NotFoundException& notFound) {
        throw RepositoryException(notFound.what());
    }
    catch (TrenchCoatException& coatError) {
        throw RepositoryException(coatError.what());
    }

}

void Service::putFilteredCoats(std::vector<TrenchCoat>& destinationVector, const std::string& sizeFilter) const {
    std::vector<TrenchCoat>& allCoats = this->repository->getAll();
    for (auto& currentCoat: allCoats) {
        if (sizeFilter.empty() || sizeFilter == currentCoat.getSize())
            destinationVector.push_back(currentCoat);
    }
}

void Service::initializeHardCodedEntities() {
    std::string colorRed("Red");
    std::string colorBlue("Blue");
    std::string colorBlack("Black");
    std::string colorOrange("Orange");
    std::string colorYellow("Yellow");
    std::string colorBrown("Brown");
    std::string colorPurple("Purple");
    std::string colorLightBlue("Light Blue");
    std::string colorPink("Pink");
    std::string sizeXS("XS");
    std::string sizeS("S");
    std::string sizeM("M");
    std::string sizeL("L");
    std::string colorDarkBrown("Dark Brown");
    std::string photographLink1("https://www.net-a-porter.com/variants/images/1647597288592595/in/w920_q60.jpg");
    std::string photographLink2(
            "https://n.nordstrommedia.com/id/sr3/ecac49b7-3b91-4c05-a4ec-544d7d1da3e6.jpeg?crop=pad&pad_color=FFF&format=jpeg&w=780&h=1196");
    std::string photographLink3(
            "https://lp2.hm.com/hmgoepprod?set=format%5Bwebp%5D%2Cquality%5B79%5D%2Csource%5B%2F72%2Fa1%2F72a1c1433674f90504b955fca3ae4dc2399fadf1.jpg%5D%2Corigin%5Bdam%5D%2Ccategory%5B%5D%2Ctype%5BDESCRIPTIVESTILLLIFE%5D%2Cres%5Bm%5D%2Chmver%5B2%5D&call=url%5Bfile%3A%2Fproduct%2Fmain%5D");
    std::string photographLink4(
            "https://lp.monki.com/app002prod?set=format%5Bwebp%5D%2Cquality%5B79%5D%2Csource%5B%2F05%2F77%2F0577f02ec6e7adc96a0a92331efc4eae927da509.jpg%5D%2Corigin%5Bdam%5D%2Ccategory%5B%5D%2Ctype%5BDESCRIPTIVESTILLLIFE%5D%2Cres%5Bm%5D%2Chmver%5B2%5D%2Ctarget%5Bhm.com%5D&call=url%5Bfile%3A%2Fproduct%2Fmain%5D");
    std::string photographLink5(
            "https://hawkbull.de/wp-content/uploads/2022/04/german20ww220trench20coat20real_1.jpg.webp");

    this->addCoat(colorRed, sizeS, 20, 2, photographLink1);
    this->addCoat(colorPink, sizeL, 25, 5, photographLink5);
    this->addCoat(colorDarkBrown, sizeM, 19.99, 8, photographLink3);
    this->addCoat(colorLightBlue, sizeS, 29.99, 3, photographLink5);
    this->addCoat(colorPurple, sizeS, 34.99, 11, photographLink4);
    this->addCoat(colorBrown, sizeXS, 14.99, 6, photographLink2);
    this->addCoat(colorOrange, sizeS, 49.99, 5, photographLink1);
    this->addCoat(colorYellow, sizeL, 19.99, 3, photographLink4);
    this->addCoat(colorBlack, sizeM, 27.99, 5, photographLink2);
    this->addCoat(colorBlue, sizeL, 32.99, 2, photographLink4);
}

TrenchCoat& Service::getCoatByColor(const std::string& coatColor) const {
    auto& allCoats = repository->getAll();
    auto iter = std::find_if(allCoats.begin(), allCoats.end(), [coatColor](const TrenchCoat& coat) -> bool {
        return coat.getColor() == coatColor;
    });
    if (iter == allCoats.end())
        throw NotFoundException("Could not find coat with color " + coatColor);
    return allCoats[iter - allCoats.begin()];
}

void Service::setUserCoatList(FileUserCoatList* _userCoatList) {
    userCoatList = _userCoatList;
}

std::vector<TrenchCoat>& Service::getUserList() const {
    return userCoatList->getUserList();
}

void Service::addCoatToUserList(TrenchCoat coat) {
    auto iter = std::find_if(userCoatList->getUserList().begin(), userCoatList->getUserList().end(), [coat](const TrenchCoat& coat2)->bool {
        return coat.getColor() == coat2.getColor();
    });
    if (iter == userCoatList->getUserList().end()){
        coat.setQuantity(1);
        userCoatList->addCoatToUserList(coat);
        userCoatList->writeToFile();
    }
    else{
        TrenchCoat& foundCoat = userCoatList->getUserList()[iter - userCoatList->getUserList().begin()];
        foundCoat.setQuantity(foundCoat.getQuantity() + 1);
        userCoatList->writeToFile();
    }
}

void Service::deleteCoatFromUserList(std::string& color) {
    auto iter = std::find_if(userCoatList->getUserList().begin(), userCoatList->getUserList().end(), [color](const TrenchCoat& coat)->bool {
        return coat.getColor() == color;
    });
    if (iter == userCoatList->getUserList().end())
        throw RepositoryException("Coat not in cart.");

}

void Service::openUserList() {
    userCoatList->displayUserCoatList();
}

