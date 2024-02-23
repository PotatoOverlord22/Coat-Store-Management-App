#pragma once

#include "FileUserCoatList.h"

class HTMLUserCoatList : public FileUserCoatList{

public:
    HTMLUserCoatList(const std::string& filename) : FileUserCoatList(filename) {}

    ~HTMLUserCoatList() override = default;

    void writeToFile() override;

    void displayUserCoatList() override;
};
