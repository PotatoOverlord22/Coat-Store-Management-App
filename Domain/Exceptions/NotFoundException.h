#pragma once

#include <exception>
#include <string>

class NotFoundException : public std::exception{

protected:
    std::string errorMsg;

public:
    NotFoundException(std::string _errorMsg = "");

    virtual const char* what();
};
