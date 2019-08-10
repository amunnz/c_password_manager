#include <stdexcept>
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
}

UI::UserChoice UI::get_user_action_choice() {

    /* This function should do all error checking itself,
    and be guaranteed to return an integer of the appropriate range */

    /* Nitpicky error checking: 
    1.) That the input is a valid integer
    2.) That the integer is one of the set {1,2,3,4,5,6,7}
    */

    // Upon failure respond to the user why the input was incorrect
    // and then prompt user to input again.

    unsigned char user_input = 5;

    if (user_input < 0 || user_input >= UI::LAST_ITEM)
        std::cout << "Value outside range" << std::endl;
    else if (user_input == UI::PRINT_ALL)
        return UI::PRINT_ALL;
    else if (user_input == UI::PRINT_SINGLE)
        return UI::PRINT_SINGLE;
    else if (user_input == UI::ADD)
        return UI::ADD;
    else if (user_input == UI::DELETE)
        return UI::DELETE;
    else if (user_input == UI::EDIT)
        return UI::EDIT;
    else if (user_input == UI::SAVE_AND_EXIT)
       return UI::SAVE_AND_EXIT;
    else if (user_input == UI::DISCARD_AND_EXIT)
       return UI::DISCARD_AND_EXIT;
}