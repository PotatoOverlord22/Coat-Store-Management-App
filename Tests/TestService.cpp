#include "TestService.h"
#include <cassert>

void TestService::testAll() {
    std::string emptyString;
    std::string coat1Color = "test-color1";
    std::string coat1Size = "XS";
    std::string coat1Link = "test-link";
    double coat1Price = 12.3;
    int coat1Quantity = 2;
    TrenchCoat testCoat1 = TrenchCoat(coat1Color, coat1Size, coat1Price, coat1Quantity, coat1Link);

    auto repository = new Repository;
    Service service = Service(*repository);
    try{
        service.addCoat(coat1Color, coat1Size, coat1Price, coat1Quantity, coat1Link);
        assert(true);
    }
    catch (std::exception&){
        assert(false);
    }
    try{
        service.addCoat(coat1Color, coat1Size, coat1Price, coat1Quantity, coat1Link);
        service.addCoat(emptyString, emptyString, coat1Price, coat1Quantity, coat1Link);
        assert(false);
    }
    catch (std::exception&){
        assert(true);
    }

    service.initializeHardCodedEntities();
    try{
        service.findCoat(coat1Color);
        service.removeCoat(coat1Color);
        assert(true);
    }
    catch (std::exception&){
        assert(false);
    }
    try{
        service.findCoat(coat1Color);
        service.removeCoat(coat1Color);
        assert(false);
    }
    catch (std::exception&){
        assert(true);
    }

    try{
        service.addCoat(coat1Color, coat1Size, coat1Price, coat1Quantity, coat1Link);
        service.updateCoatSize(coat1Color, "S");
        service.updateCoatPrice(coat1Color, 10.2);
        service.updateCoatQuantity(coat1Color, 3);
        service.updateCoatPhotoLink(coat1Color, "test-service-photo-link1");
        service.removeCoat(coat1Color);
        assert(true);
    }
    catch (std::exception&){
        assert(false);
    }
    try{
        service.updateCoatColor(coat1Color, "some-color");
        service.updateCoatSize(coat1Color, "S");
        service.updateCoatPrice(coat1Color, 10.2);
        service.updateCoatQuantity(coat1Color, 3);
        service.updateCoatPhotoLink(coat1Color, "test-service-photo-link1");
        assert(false);
    }
    catch (std::exception&){
        assert(true);
    }

    try{
        service.addCoat(coat1Color, coat1Size, coat1Price, coat1Quantity, coat1Link);
        std::string newCoat1Color("new-color");
        service.updateCoatColor(coat1Color, newCoat1Color);
        service.updateCoatPrice(newCoat1Color, 23.4);
        service.updateCoatSize(newCoat1Color, "XL");
        service.updateCoatQuantity(newCoat1Color, 10);
        service.updateCoatPhotoLink(newCoat1Color, "test-service-photo-link2");
        assert(true);
    }
    catch (std::exception&){
        assert(false);
    }

    std::vector<TrenchCoat> filteredCoats;
    std::vector<TrenchCoat> allCoats = service.getAllCoats();
    service.putFilteredCoats(filteredCoats, "");
    assert(filteredCoats.size() == allCoats.size());
    delete repository;
}
