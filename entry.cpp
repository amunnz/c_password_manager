#include "entry.h"

void Entry::print_single_entry() const {
    std::cout << title << " " << username << " " << password << std::endl;
}

void Entry::print_entry_title(){
    std::cout << title;
}

std::string Entry::entry_to_string() {
	std::string entryString=title+","+username + "," + password;
	return entryString;
}


Entry::Entry(std::string& t, std::string& u, std::string& p):
    title(t),
    username(u),
    password(p) {}