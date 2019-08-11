#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <iostream>

class Entry {
private:
    std::string title;
    std::string username;
    std::string password;

    void print_single_entry() const;
};

#endif