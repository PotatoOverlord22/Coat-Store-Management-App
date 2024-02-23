#pragma once

#include "../TrenchCoat.h"
#include <vector>

class UserCoatList {

protected:
    std::vector<TrenchCoat> coatList;

public:
    void addCoatToUserList(TrenchCoat&);

    void deleteTrenchCoatByIndex(int);

    std::vector<TrenchCoat>& getUserList();
};
