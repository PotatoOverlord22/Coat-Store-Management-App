#include "Repository.h"
#include "../Exceptions/FileException.h"
#include <algorithm>
#include <iostream>
#include <fstream>

Repository::Repository() = default;

Repository::Repository(const std::string& filename) {
    this->filename = filename;
    readFromFile();
}

Repository::~Repository() = default;

std::vector<TrenchCoat>& Repository::getAll() {
    return this->data;
}

void Repository::addCoat(TrenchCoat& newCoat) {
    this->data.push_back(newCoat);
    writeToFile();
}

bool Repository::removeCoat(TrenchCoat& coatToRemove) {
    auto coatToRemovePosition = std::find(data.begin(), data.end(), coatToRemove);
    if (coatToRemovePosition == data.end())
        return false;
    else {
        data.erase(coatToRemovePosition);
        writeToFile();
        return true;
    }
}

bool Repository::updateCoat(TrenchCoat& coatToUpdate, const std::string& newColor, const std::string& newSize,
                            const double newPrice, const int newQuantity, const std::string& newPhotoLink) {
    auto foundCoatIter = std::find(data.begin(), data.end(), coatToUpdate);
    if (foundCoatIter == data.end())
        return false;
    TrenchCoat& coat = data[foundCoatIter - data.begin()];
    coat.setColor(newColor);
    coat.setSize(newSize);
    coat.setPrice(newPrice);
    coat.setQuantity(newQuantity);
    coat.setPhotograph(newPhotoLink);

    writeToFile();
    return true;
}

void Repository::readFromFile() {
    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
        throw FileException("Could not open file " + filename + " for reading purposes.");

    TrenchCoat coat;
    while (file >> coat)
        data.push_back(coat);
    file.close();
}

void Repository::writeToFile() const {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open())
        throw FileException("Could not open file " + filename + " for writing purposes.");

    for (auto& coat : data)
        file << coat << '\n';

    file.close();
}

bool Repository::updateFile() const {
    try{
        writeToFile();
        return true;
    }
    catch (FileException&) {
        return false;
    }
}

bool Repository::removeCoatByIndex(int index) {
    if (index < 0 || index >= data.size())
        return false;
    this->data.erase(this->data.begin() + index);
    this->writeToFile();
    return true;
}


