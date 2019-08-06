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

    // This is the code for case 6, save to file and close
    if (!cryptographic_data) {
        cryptographic_data = new CryptoG(message, message.length());
    }
    cryptographic_data->encrypt_and_write_to_file();
    delete cryptographic_data;

    return 0;
}