#include "TrenchCoat.h"
#include <vector>

TrenchCoat::TrenchCoat(const std::string& color, const std::string& size, double price, int quantity,
                       const std::string& photo) {
    this->color = color;
    this->size = size;
    this->price = price;
    this->quantity = quantity;
    this->photograph = photo;
}

TrenchCoat::TrenchCoat(const TrenchCoat& coatToCopy) {
    this->color = coatToCopy.getColor();
    this->size = coatToCopy.getSize();
    this->price = coatToCopy.getPrice();
    this->quantity = coatToCopy.getQuantity();
    this->photograph = coatToCopy.getPhotograph();
}


TrenchCoat::~TrenchCoat() = default;

std::string TrenchCoat::getSize() const {
    return this->size;
}

double TrenchCoat::getPrice() const {
    return this->price;
}

int TrenchCoat::getQuantity() const {
    return this->quantity;
}

std::string TrenchCoat::getColor() const {
    return this->color;
}

std::string TrenchCoat::getPhotograph() const {
    return this->photograph;
}

void TrenchCoat::setSize(const std::string& newSize) {
    this->size = newSize;
}

void TrenchCoat::setPrice(const double newPrice) {
    this->price = newPrice;
}

void TrenchCoat::setQuantity(const int newQuantity) {
    this->quantity = newQuantity;
}

void TrenchCoat::setColor(const std::string& newColor) {
    this->color = newColor;
}

void TrenchCoat::setPhotograph(const std::string& newPhotographLink) {
    this->photograph = newPhotographLink;
}

bool TrenchCoat::operator==(const TrenchCoat& other) {
    if (this == &other)
        return true;
    if (this->getColor() != other.getColor())
        return false;
    if (this->getSize() != other.getSize())
        return false;
    if (this->getPrice() != other.getPrice())
        return false;
    if (this->getQuantity() != other.getQuantity())
        return false;
    if (this->getPhotograph() != other.getPhotograph())
        return false;
    return true;
}

bool TrenchCoat::operator!=(const TrenchCoat& other) {
    return this != &other;
}

std::string TrenchCoat::toString() const {
    char priceTwoDecimals[25];
    sprintf(priceTwoDecimals, "%.2f", this->price);
    return this->color + " coat | " + this->size + " | " + "$" + std::string(priceTwoDecimals) +
           " | x" + std::to_string(this->quantity) + " | " + this->photograph;
}

std::ostream& operator<<(std::ostream& output, const TrenchCoat& coat) {
    output << coat.color << ',' << coat.size << ',' << coat.price << ',' << coat.quantity << ',' << coat.photograph;
    return output;
}

std::istream& operator>>(std::istream& input, TrenchCoat& coat) {
    std::string line;
    std::getline(input, line);
    std::string field;
    std::vector<std::string> coatFields;
    int i = 0;
    while (i < line.size()){
        if (line[i] == ','){
            coatFields.push_back(field);
            field.clear();
        }
        else{
            field += line[i];
        }
        i++;
    }
    coatFields.push_back(field);
    if (coatFields.size() != 5)
        return input;

    coat.color = coatFields[0];
    coat.size = coatFields[1];
    coat.price = std::stod(coatFields[2]);
    coat.quantity = std::stoi(coatFields[3]);
    coat.photograph = coatFields[4];

    return input;
}
