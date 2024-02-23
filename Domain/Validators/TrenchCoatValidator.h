#pragma once

#include "../TrenchCoat.h"
#include "../Exceptions/TrenchCoatException.h"

class TrenchCoatValidator {
public:
    TrenchCoatValidator();

    static void validate(const TrenchCoat&);
};