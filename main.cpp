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

    // Do database stuff...
    UI::print_home_screen();
    
    

    const std::string message = "Title,Username,Password\nFacebook,email@address.com,myfbpassword";

    while(true) {
        int index_choice = UI::get_user_input();
        switch (index_choice) {
            case 1: { // Print all
                std::cout << "To be implemented" << std::endl;
            }
            case 2: { // Print single
                std::cout << "To be implemented" << std::endl;
            }
            case 3: { // Add entry

            }
            case 4: { // Delete entry

            }
            case 5: { // Edit entry

            }
            case 6: { // Save and exit
                if (!cryptographic_data) {
                    cryptographic_data = new CryptoG(message, message.length());
                }
                cryptographic_data->encrypt_and_write_to_file();
                delete cryptographic_data;
                break;
            }
            case 7: { // Discard and exit
                break;
            }
        }
    }

    return 0;
}