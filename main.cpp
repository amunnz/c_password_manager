#include "cryptog.h"
#include "ui.h"

int main(int argc, char** argv) {

    const std::string message = "Title,Username,Password\nFacebook,email@address.com,myfbpassword";

    // Initialise a pointer to our object. If no file is provided, point to 0x0, otherwise allocate
    // a new CryptoG object on the heap and point to it.
    CryptoG* cryptographic_data = (argc == 1) ? nullptr : new CryptoG();

    // Do database stuff...
    UI::print_home_screen();

    // If cryptographic_data hasn't been initialised away from NULLPTR, initialise it
    if (!cryptographic_data) {
        cryptographic_data = new CryptoG(message, message.length());
    }
    cryptographic_data->encrypt_and_write_to_file();
         
    
    return 0;
}