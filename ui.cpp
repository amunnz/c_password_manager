#include "ui.h"

void UI::print_home_screen() {
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "Welcome to c_password_manager" << std::endl;
    std::cout << "1) Print all database entries" << std::endl;
    std::cout << "2) Print a single database entry" << std::endl;
    std::cout << "3) Add an entry to the database" << std::endl;
    std::cout << "4) Delete an entry from the database" << std::endl;
    std::cout << "5) Edit an entry in the database" << std::endl;
    std::cout << "6) Save to file and close" << std::endl;
    std::cout << "7) Discard changes and close" << std::endl;
    std::cout << "Please enter the index of the action you wish to perform: ";
}