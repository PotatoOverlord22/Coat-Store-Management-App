#pragma once

#include "../Repository/Repository.h"
#include "../Validators/TrenchCoatValidator.h"
#include "../UserLists/FileUserCoatList.h"

class Service {

private:
    Repository* repository;
    TrenchCoatValidator coatValidator;
    FileUserCoatList* userCoatList;

public:
    Service(Repository& repository);

    ~Service();

    void setUserCoatList(FileUserCoatList* _userCoatList);

    std::vector<TrenchCoat>& getUserList() const;

    void addCoatToUserList(TrenchCoat);

    void deleteCoatFromUserList(std::string& color);

    void openUserList();

    void addCoat(std::string& color, const std::string& size, double price, int quantity, std::string& photo);

    void removeCoat(const std::string& color) const;

    void initializeHardCodedEntities();

    std::vector<TrenchCoat>& getAllCoats() const;

    TrenchCoat& getCoatByColor(const std::string& coatColor) const;

    bool findCoat(const std::string& coatColor) const;

    int getCoatIndex(const std::string& color) const;

    void
    updateAllCoatFields(const std::string& coatToUpdateColor, const std::string& newColor, const std::string& newSize,
                        double newPrice, int newQuantity, const std::string& newPhoto) const;

    void updateCoatColor(const std::string& coatToUpdateColor, const std::string& newColor) const;

    void updateCoatSize(const std::string& coatToUpdateColor, const std::string& newSize) const;

    void updateCoatPhotoLink(const std::string& coatToUpdateColor, const std::string& newLink) const;

    void updateCoatPrice(const std::string& coatToUpdateColor, const double newPrice) const;

    void updateCoatQuantity(const std::string& coatToUpdateColor, const int newQuantity) const;

    void putFilteredCoats(std::vector<TrenchCoat>& destinationVector, const std::string& sizeFilter) const;
};
