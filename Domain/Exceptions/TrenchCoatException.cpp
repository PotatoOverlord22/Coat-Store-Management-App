//
// Created by raul on 17.05.2023.
//

#include "TrenchCoatException.h"

TrenchCoatException::TrenchCoatException(std::vector<std::string> _errors) : errors(std::move(_errors)) {

}

std::vector<std::string> TrenchCoatException::getErrors() const {
    return errors;
}

const char* TrenchCoatException::what() {
    msg.clear();
    for (auto& errorMsg : errors)
        msg += errorMsg + '\n';
    return msg.c_str();
}
