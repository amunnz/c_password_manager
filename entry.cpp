#include "entry.h"

void Entry::print_single_entry() const {
    std::cout << title << " " << username << " " << password << std::endl;
}

void Entry::print_entry_title(){
    std::cout << title;
}



Entry::Entry(std::string& t, std::string& u, std::string& p):
    title(t),
    username(u),
    password(p) {}