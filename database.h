#ifndef DATABASE_H 
#define DATABASE_H

#include <string>
#include <iostream>
#include <vector>
#include "entry.h"

class Database {
private:
	//Members
	std::vector<Entry> Entries;
	//Member Functions
	std::vector<std::string> delimitString(std::string& s,std::string& delimiter);


    
public:
//Constructors
	Database(std::string& s); //constructor for existing decrypted database
	Database(Entry& e); //constructor for new data base with first entry

//Member Functions
	 //function adds entry class objects to the Entries vector
	//function returns Entries vector size
	void add_entry(Entry& entry);
	void database_size(void) const; 
	void print_entry_titles(void);
	void delete_entry(int c);
	void edit_entry(int c,Entry& entry);
	std::string serialiseDataBase(void);
	//std::vector<std::string> delimitString(std::string& s,std::string& delimiter);

};

#endif