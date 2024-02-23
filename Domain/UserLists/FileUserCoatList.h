#pragma once

#include "UserCoatList.h"

#include <utility>

class FileUserCoatList : public UserCoatList{

protected:
    std::string filename;

public:
    FileUserCoatList(std::string  file) : UserCoatList(), filename(std::move(file)) {}

    virtual ~FileUserCoatList() = default;

    virtual void writeToFile() = 0;

    virtual void displayUserCoatList() = 0;
};
