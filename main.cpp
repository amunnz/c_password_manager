#include "cryptog.h"
#include "ui.h"

int main(int argc, char** argv) {

    CryptoG* cryptographic_data = nullptr;

    if (argc == 2) { // File argument present.
        
        // Create file object
        FileSource fs("database", false /* Do not pump all bytes immediately*/);

        // Create new CryptoG object on the heap, reading and decrypting file data.
        cryptographic_data = new CryptoG(fs);
    }

    const std::string message = "Title,Username,Password\nFacebook,email@address.com,myfbpassword";

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