#include "TrenchCoatValidator.h"

TrenchCoatValidator::TrenchCoatValidator() = default;

void TrenchCoatValidator::validate(const TrenchCoat& coat) {
    std::vector<std::string> errors;

    if (coat.getColor().size() < 3)
        errors.emplace_back("Color must be at least 3 chars long");

    if (coat.getSize().empty())
        errors.emplace_back("Size must not be empty.");

    if (coat.getPrice() < 0)
        errors.emplace_back("Price must be a positive number.");

    if (coat.getQuantity() < 0)
        errors.emplace_back("Quantity must be a positive integer.");

    if (!errors.empty())
    throw TrenchCoatException(errors);
}
