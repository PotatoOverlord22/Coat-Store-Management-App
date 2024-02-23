#pragma once

#include "FileUserCoatList.h"

class CSVUserCoatList : public FileUserCoatList {

public:
    CSVUserCoatList(const std::string& filename) : FileUserCoatList(filename) {}

    ~CSVUserCoatList() override = default;

    void writeToFile() override;

    void displayUserCoatList() override;
};
