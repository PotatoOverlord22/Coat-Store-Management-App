#include "FileException.h"

#include <utility>

FileException::FileException(std::string  errorMsg) : errorMessage(std::move(errorMsg)) {

}

const char* FileException::what() {
    return errorMessage.c_str();
}
