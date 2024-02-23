#pragma  once

#include <exception>
#include <string>

class FileException : public std::exception {

protected:
    std::string errorMessage;

public:
    FileException(std::string errorMsg = "");

    virtual const char* what();
};
