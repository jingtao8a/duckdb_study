#include "../include/texttable.hpp"

int main() {
    TextTable textTable;
    textTable.add("hello");
    textTable.add("fjdask");
    textTable.add("hello");
    textTable.add("fjdask");
    textTable.endOfRow();
    textTable.add("hello");
    textTable.add("fjdask");
    textTable.add("hello");
    textTable.add("fjdask");
    textTable.endOfRow();
    
    std::cout << textTable;
    return 0;
}