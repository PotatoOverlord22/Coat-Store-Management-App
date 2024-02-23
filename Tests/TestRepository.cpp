#include "TestRepository.h"
#include "../Repository/Repository.h"
#include <cassert>

void TestRepository::testAll() {
    std::string coat1Color = "test-color1";
    std::string coat2Color = "test-color2";
    std::string coat3Color = "test-color3";
    std::string coat1Size = "XS";
    std::string coat1Link = "test-link";
    double coat1Price = 12.3;
    int coat1Quantity = 2;
    TrenchCoat testCoat1 = TrenchCoat(coat1Color, coat1Size, coat1Price, coat1Quantity, coat1Link);
    TrenchCoat testCoat2 = TrenchCoat(coat2Color, coat1Size, coat1Price, coat1Quantity, coat1Link);
    TrenchCoat testCoat3 = TrenchCoat(coat3Color, coat1Size, coat1Price, coat1Quantity, coat1Link);

    Repository repository;
    repository.addCoat(testCoat1);
    assert(repository.removeCoat(testCoat3) == false);
    assert(repository.removeCoat(testCoat1) == true);
    assert(repository.removeCoat(testCoat3) == false);

    repository.addCoat(testCoat1);
    repository.addCoat(testCoat2);
    repository.addCoat(testCoat3);

    std::vector<TrenchCoat> data = repository.getAll();
    assert(data.size() == 3);

    assert(repository.updateCoat(testCoat1, coat2Color, coat1Size, coat1Price, coat1Quantity, coat1Link) == true);
    testCoat1.setColor(coat2Color);
    assert(repository.removeCoat(testCoat3) == true);
    assert(repository.updateCoat(testCoat3, coat2Color, coat1Size, coat1Price, coat1Quantity, coat1Link) == false);
}
