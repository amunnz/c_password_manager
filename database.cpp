#include "database.h"

void Database::add_entry(Entry& entry) {
	Entries.push_back(entry);
}

void Database::database_size(void) const{
	std::cout << "Database size: " << Entries.size() << std::endl;
}

void Database::print_entry_titles(void){
	//Loop through Entries vector, and print the names
	for( std::size_t i=0; i<Entries.size(); i++) {
		std::cout << "Entry " << i << ") ";
		Entries[i].print_entry_title();
		std::cout << std::endl;
	}
}

void Database::delete_entry(int c) {
	Entries.erase (Entries.begin()+c);
}

void Database::edit_entry(int c,Entry& entry) {
	Entries[c]=entry;
}


std::vector<std::string> Database::delimitString(std::string& s,std::string& delimiter) { 
	//takes insperation from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	std::vector<std::string> delimitedString;
	//initialise a position flag
	std::size_t pos = 0; //size_t is a type of iterator unsigned integer
	std::string s_entry; //this is a temporty string to store an entry after its been identified

	//npos is the largest number that fits into a size_t, its a break condition so you dont get crazy shit I guess
	while ((pos = s.find(delimiter)) != std::string::npos) {
    	s_entry = s.substr(0, pos);
 		//put the string chunk into the delimited vector
    	delimitedString.push_back(s_entry);
    	s.erase(0, pos + delimiter.length());
	}
	//Push  the last string into the vector
	delimitedString.push_back(s);
	return delimitedString;
}

std::string Database::serialiseDataBase(void) {
	std::cout << "hello world" << std::endl;
	std::string limitedString;
	//COnvert an entry into a string
	//entry_to_string()
	for( std::size_t i=0; i<Entries.size(); i++) {
		std::cout << Entries[i].entry_to_string() << std::endl;
		limitedString.append(Entries[i].entry_to_string()+"\n");
	}
	std::cout << "WORKING?" << std::endl;
	std::cout << limitedString << std::endl;
	return limitedString;
}


Database::Database(std::string& s) {
	//sanity print the input string
	std::cout << s << std::endl;

	//set the delimiter, in this case its "\n"
	std::string delimiter = "\n";
	std::vector <std::string> EntryList;
	EntryList=delimitString(s,delimiter);

	//set up a vector for each entry string to be delimited by ","
	std::string delimiter2 = ",";
	std::vector <std::string> s_entry;

	//Loop through the EntryList, and convert each item into an entry
	//This then gets pused into the Entries vector
	for( std::size_t i=0; i<EntryList.size(); i++) {
		s_entry=delimitString(EntryList[i],delimiter2);
		Entry entry(s_entry[0],s_entry[1],s_entry[2]); //this might be a shit thing to do?
		Entries.push_back(entry);
	}
}

Database::Database(Entry& entry) {
	Entries.push_back(entry);
}