#ifndef ENTRY_H 
#define ENTRY_H

#include <string>
#include <iostream>

class Entry {
private:
    std::string title;
    std::string username;
    std::string password;

    //void print_single_entry() const;


public:
    Entry(std::string& t, std::string& u, std::string& p); //this is a constructor? COMMENT YOU DONGUS!
    void print_single_entry() const;
    void print_entry_title();
};

#endif