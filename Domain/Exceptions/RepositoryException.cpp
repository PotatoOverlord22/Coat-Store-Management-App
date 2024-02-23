#include "RepositoryException.h"

RepositoryException::RepositoryException(std::string errorMsg) : errorMessage(std::move(errorMsg)) {

}

const char* RepositoryException::what() {
    return errorMessage.c_str();
}
