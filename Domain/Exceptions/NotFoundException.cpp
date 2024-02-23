#include "NotFoundException.h"

NotFoundException::NotFoundException(std::string _errorMsg) : errorMsg(std::move(_errorMsg)) {

}

const char* NotFoundException::what() {
    return errorMsg.c_str();
}
