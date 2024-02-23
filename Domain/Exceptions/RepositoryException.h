#pragma once

#include <exception>
#include <string>

class RepositoryException : public std::exception{

protected:
    std::string errorMessage;

public:
    RepositoryException(std::string errorMsg = "");

    virtual const char* what();
};