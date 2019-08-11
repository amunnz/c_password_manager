#include <algorithm>
#include "ui.h"

void UI::print_home_screen() {
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "Welcome to c_password_manager" << std::endl;
    std::cout << "0) Print all database entries" << std::endl;
    std::cout << "1) Print a single database entry" << std::endl;
    std::cout << "2) Add an entry to the database" << std::endl;
    std::cout << "3) Delete an entry from the database" << std::endl;
    std::cout << "4) Edit an entry in the database" << std::endl;
    std::cout << "5) Save to file and close" << std::endl;
    std::cout << "6) Discard changes and close" << std::endl;
}

bool UI::is_number(const std::string& s) {

    /* find_if
    this is c++11 code
    returns an iterator to the first element where the predicate returns true
    the predicate is the third argument, a lambda function aka anonymous function
    the form of a lambda in c++ is: [capture](parameters) -> return_type { function_body }
    here the return type is implied as boolean*/
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(),
                                      [](char c) { return !std::isdigit(c); }
                                      ) == s.end();
}

UI::UserChoice UI::get_user_action_choice() {

    std::string user_input_string;
    std::getline(std::cin, user_input_string);

    UserChoice choice = LAST_ITEM; // Initialise to an error
    int user_input_int;

    // Check that the input is an integer
    if (!is_number(user_input_string)) {
        std::cout << "Please enter an integer." << std::endl;
        return LAST_ITEM;
    } else {
        user_input_int = std::stoi(user_input_string);
    }

    // Check that the integer falls within the index range
    if (user_input_int < 0 || user_input_int >= LAST_ITEM)
        std::cout << "Please enter an integer between " << 0 << " and " << LAST_ITEM << std::endl;
    else if (user_input_int == PRINT_ALL)
        choice = PRINT_ALL;
    else if (user_input_int == PRINT_SINGLE)
        choice = PRINT_SINGLE;
    else if (user_input_int == ADD)
        choice = ADD;
    else if (user_input_int == DELETE)
        choice = DELETE;
    else if (user_input_int == EDIT)
        choice = EDIT;
    else if (user_input_int == SAVE_AND_EXIT)
        choice = SAVE_AND_EXIT;
    else if (user_input_int == DISCARD_AND_EXIT)
        choice = DISCARD_AND_EXIT;

    return choice;
}