#include "HTMLUserCoatList.h"
#include "../Exceptions/FileException.h"
#include <fstream>

void HTMLUserCoatList::writeToFile() {
    std::ofstream output;
    output.open(filename);
    if (!output.is_open())
        throw FileException("Could not open file " + filename);

    output << "<!DOCTYPE html>\n";
    output << "<html>\n";
    output << "<head>\n";
    output << "<title>Coats</title>\n";
    output << "</head>\n";
    output << "<body>\n";
    output << "<table border=\"1\">\n";
    output << "<tr>\n";
    output << "<td>Color</td>\n";
    output << "<td>Size</td>\n";
    output << "<td>Price</td>\n";
    output << "<td>Quantity</td>\n";
    output << "<td>Photo link</td>\n";
    output << "</tr>\n";
    for (auto coat : coatList)
    {
        output << "<tr>\n";
        output << "<td>" << coat.getColor() << "</td>\n";
        output << "<td>" << coat.getSize() << "</td>\n";
        output << "<td>" << coat.getPrice() << "</td>\n";
        output << "<td>" << coat.getQuantity() << "</td>\n";
        output << "<td><a href=\"" << coat.getPhotograph() << "\">Link</a></td>\n";
        output << "</tr>\n";
    }
    output << "</table>\n";
    output << "</body>\n";
    output << "</html>\n";
    output.close();
}

void HTMLUserCoatList::displayUserCoatList() {
    std::string command = "open " + filename;
    system(command.c_str());
}
