#include "cryptog.h"
#include "ui.h"
#include "entry.h"
#include "database.h"

int main(int argc, char** argv) {

   CryptoG* cryptographic_data = nullptr;

    if (argc == 2) { // File argument present.
        
        // Create file object
        FileSource fs("database", false /* Do not pump all bytes immediately*/);

        // Create new CryptoG object on the heap, reading and decrypting file data.
        cryptographic_data = new CryptoG(fs);
    }

    const std::string message = "Title,Username,Password\nFacebook,email@address.com,myfbpassword";
    //*******************TEST CODE***************************************
    std::string testString = "Facebook,email@address.com,myfbpassword\nMoosebook,moosemail@address.com,myMoosebookpassword\nCatbook,catemail@address.com,myCatBookPassword";
    std::cout << "Using a test string: \n" << testString << std::endl;

    //Check Entry class
    std::cout << "+++++++++++++Checking entry class+++++++++++++" << std::endl;
    std::string s1="Entrybook";
    std::string s2="Entry@address.com";
    std::string s3="myEntrypassword";
    Entry testEntry(s1,s2,s3);
    testEntry.print_single_entry();
    std::cout << "+++++++++Done Checking entry class+++++++++++++" << std::endl;

    std::cout << "+++++++++++++Checking database class+++++++++++++" << std::endl;
    std::cout << "Checking entry constructor..." << std::endl;
    //build a database using entry 
    Database testDB(testEntry);
    testDB.database_size();

    std::cout << "Checking add entry function..." << std::endl;
    testDB.add_entry(testEntry);
    testDB.database_size();
    

    std::cout << "Checking string constructor..." << std::endl;
    //build a database using a string constructor
    Database testDB2(testString);
    testDB2.database_size();
    std::cout << "Checking print entry titles function..." << std::endl;
    testDB2.print_entry_titles();
    std::cout << "Checking edit entry function..." << std::endl;
    int c=1;
    testDB2.edit_entry(c,testEntry);
    testDB2.print_entry_titles();
    std::cout << "Checking delete entry function..." << std::endl;
    testDB2.delete_entry(c);
    testDB2.print_entry_titles();
    std::cout << "Checking serialise function..." << std::endl;
    std::string limitedString=testDB2.serialiseDataBase();
    std::cout << limitedString << std::endl;
    std::cout << "+++++++++Done Checking database class+++++++++++++" << std::endl;




    bool continue_running = true;
    while(continue_running) {
        UI::print_home_screen();
        switch (UI::get_user_action_choice()) {
            case UI::PRINT_ALL:
                break;

            case UI::PRINT_SINGLE:
                break;

            case UI::ADD:
                break;

            case UI::DELETE:
                break;

            case UI::EDIT:
                break;

            case UI::SAVE_AND_EXIT:
                if (!cryptographic_data) {
                    cryptographic_data = new CryptoG(message, message.length());
                }
                cryptographic_data->encrypt_and_write_to_file();
                delete cryptographic_data;
                continue_running = false;
                break;
            
            case UI::DISCARD_AND_EXIT:
                continue_running = false;
                break;
        
            case UI::LAST_ITEM:
                std::cerr << "Error parsing user input to integer. Try again" << std::endl;
                break;
        }
    }

    return 0;
}