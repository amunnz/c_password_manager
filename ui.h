#ifndef UI_H
#define UI_H

#include <iostream>

class UI {
    public:
    enum UserChoice {
        PRINT_ALL, PRINT_SINGLE, ADD, DELETE, EDIT, SAVE_AND_EXIT, DISCARD_AND_EXIT, LAST_ITEM
    };
    static void print_home_screen();
    static UserChoice get_user_action_choice();
};

#endif