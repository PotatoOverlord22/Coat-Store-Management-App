#pragma once

#include <vector>
#include <string>

class TrenchCoatException : public std::exception{

private:
    std::vector<std::string> errors;
    std::string msg;

public:
    TrenchCoatException(std::vector<std::string> errors);

    std::vector<std::string> getErrors() const;

    virtual const char* what();
};
