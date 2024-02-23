#pragma once

#include "../Domain/TrenchCoat.h"
#include <vector>

class Repository {
private:
    std::string filename;
    std::vector<TrenchCoat> data;

public:
    Repository();

    Repository(const std::string& filename);

    ~Repository();

    std::vector<TrenchCoat>& getAll();

    void addCoat(TrenchCoat& newCoat);

    bool removeCoat(TrenchCoat& coatToRemove);

    bool removeCoatByIndex(int index);

    bool updateCoat(TrenchCoat& coatToUpdate, const std::string& newColor, const std::string& newSize, const double newPrice,
               const int newQuantity, const std::string& newPhotoLink);

    bool updateFile() const;

private:
    void readFromFile();

    void writeToFile() const;
};
