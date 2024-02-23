#pragma once

#include <string>
#include <iostream>

class TrenchCoat {
private:
    std::string color;
    std::string size;
    double price;
    int quantity;
    std::string photograph;

public:
    explicit TrenchCoat(const std::string& color = "", const std::string& size = "", double price = 0, int quantity = 0,
               const std::string& photo = "");

    TrenchCoat(const TrenchCoat&);

    ~TrenchCoat();

    std::string getSize() const;

    double getPrice() const;

    int getQuantity() const;

    std::string getColor() const;

    std::string getPhotograph() const;

    void setSize(const std::string& newSize);

    void setPrice(double newPrice);

    void setQuantity(int newQuantity);

    void setColor(const std::string& newColor);

    void setPhotograph(const std::string& newPhotographLink);

    bool operator==(const TrenchCoat&);

    bool operator!=(const TrenchCoat&);

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& output, const TrenchCoat& coat);

    friend std::istream& operator>>(std::istream& input, TrenchCoat& coat);
};