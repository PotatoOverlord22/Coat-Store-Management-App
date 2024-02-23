#include "TestTrenchCoat.h"
#include <cassert>

void TestTrenchCoat::testConstructorDestructor() {
    TrenchCoat trenchCoat1 = TrenchCoat();
    TrenchCoat trenchCoat2 = TrenchCoat(std::string("test-color"), std::string("XS"), 13.2, 1,
                                        std::string("test-link"));
    TrenchCoat trenchCoat3 = TrenchCoat(trenchCoat2);
}

void TestTrenchCoat::testGettersSetters() {
    TrenchCoat testCoat1 = TrenchCoat();
    assert(testCoat1.getPrice() == 0);
    assert(testCoat1.getSize().empty());
    assert(testCoat1.getQuantity() == 0);
    assert(testCoat1.getColor().empty());
    assert(testCoat1.getPhotograph().empty());

    testCoat1.setPrice(20.03);
    assert(testCoat1.getPrice() == 20.03);
    std::string newSize = "XXL";
    testCoat1.setSize(newSize);
    assert(testCoat1.getSize() == "XXL");
    testCoat1.setQuantity(10);
    assert(testCoat1.getQuantity() == 10);
    std::string newColor = "blue";
    testCoat1.setColor(newColor);
    assert(testCoat1.getColor() == newColor);
    std::string newPhotographLink = "somelink.com";
    testCoat1.setPhotograph(newPhotographLink);
    assert(testCoat1.getPhotograph() == newPhotographLink);
}

void TestTrenchCoat::testOperators() {
    std::string oldColor = "test-color";
    std::string oldSize = "XS";
    std::string oldLink = "test-link";
    double oldPrice = 12.3;
    int oldQuantity = 2;

    TrenchCoat testCoat1 = TrenchCoat(oldColor, oldSize, oldPrice, oldQuantity, oldLink);
    TrenchCoat testCoat2 = TrenchCoat(testCoat1);
    assert(testCoat1 == testCoat1);
    assert(testCoat1 == testCoat2);

    std::string newSize = "S";
    testCoat1.setSize(newSize);
    assert(testCoat1 != testCoat2);
    assert(!(testCoat1 == testCoat2));
    testCoat1.setSize(oldSize);

    std::string newColor = "Brown";
    testCoat1.setColor(newColor);
    assert(testCoat1 != testCoat2);
    assert(!(testCoat1 == testCoat2));
    testCoat1.setColor(oldColor);

    std::string newLink = "some-link";
    testCoat2.setPhotograph(newLink);
    assert(testCoat1 != testCoat2);
    assert(!(testCoat1 == testCoat2));
    testCoat2.setPhotograph(oldLink);

    testCoat2.setPrice(150);
    assert(testCoat2 != testCoat1);
    assert(!(testCoat2 == testCoat1));
    testCoat2.setPrice(oldPrice);

    testCoat1.setQuantity(20);
    assert(!(testCoat2 == testCoat1));

}

void TestTrenchCoat::testToString(){
    std::string color = "test-color";
    std::string size = "XS";
    std::string link = "test-link";
    double price = 12.35;
    int quantity = 2;
    TrenchCoat coat(color, size, price, quantity, link);
    std::string coatString("test-color coat | XS | $12.35 | x2 | test-link");
    assert(coat.toString() == coatString);
}

void TestTrenchCoat::testAll() {
    this->testConstructorDestructor();
    this->testGettersSetters();
    this->testToString();
    this->testOperators();
}

