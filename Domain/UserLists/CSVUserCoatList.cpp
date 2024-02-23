#include "CSVUserCoatList.h"
#include <fstream>
#include "../Exceptions/FileException.h"

void CSVUserCoatList::writeToFile() {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open())
        throw FileException("Could not open file " + filename);
    for (auto& coat : coatList)
        file << coat;
    file.close();
}

void CSVUserCoatList::displayUserCoatList() {
    std::string command = "libreoffice --calc " + filename;
    system(command.c_str());
}
