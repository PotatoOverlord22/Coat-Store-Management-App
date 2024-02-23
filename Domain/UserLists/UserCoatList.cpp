//
// Created by raul on 17.05.2023.
//

#include "UserCoatList.h"

void UserCoatList::addCoatToUserList(TrenchCoat& coat) {
    coatList.push_back(coat);
}

void UserCoatList::deleteTrenchCoatByIndex(int index) {
    coatList.erase(coatList.begin() + index);
}

std::vector<TrenchCoat>& UserCoatList::getUserList() {
    return coatList;
}
