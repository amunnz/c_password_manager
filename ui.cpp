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
    This is c++11 code
    find_if returns an iterator to the first element where the predicate returns true.
    The predicate is the third argument, a lambda function aka anonymous function
    The form of a lambda in c++ is:
    [capture](parameters) -> return_type { function_body }
    here the return type is implied as boolean
    The lambda is applied starting at the element at s.begin() moving forward until it returns
    true or it reaches s.end(). It then returns a pointer to that element, which is compared to s.end().
    i.e. return true if the string is not empty and no non-integer digits were found.
    */
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(),
                                      [](char c) { return !std::isdigit(c); }
                                      ) == s.end();
}

UI::UserChoice UI::get_user_action_choice() {

    std::string user_input_string;
    std::getline(std::cin, user_input_string);

    int user_input_int = LAST_ITEM; // Initialise to an error

    // Check that the input is an integer
    if (!is_number(user_input_string)) {
        std::cout << "Please enter an integer." << std::endl;
        return LAST_ITEM;
    } else {
        user_input_int = std::stoi(user_input_string);
    }

    // Check that the integer falls within the index range
    if (user_input_int < 0 || user_input_int >= LAST_ITEM)
        std::cout << "Please enter an integer between " << 0 << " and " << LAST_ITEM - 1 << std::endl;
    else if (user_input_int == PRINT_ALL)
        return PRINT_ALL;
    else if (user_input_int == PRINT_SINGLE)
        return PRINT_SINGLE;
    else if (user_input_int == ADD)
        return ADD;
    else if (user_input_int == DELETE)
        return DELETE;
    else if (user_input_int == EDIT)
        return EDIT;
    else if (user_input_int == SAVE_AND_EXIT)
        return SAVE_AND_EXIT;
    else if (user_input_int == DISCARD_AND_EXIT)
        return DISCARD_AND_EXIT;

    return LAST_ITEM;
}