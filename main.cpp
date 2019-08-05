#include "cryptog.h"
#include "ui.h"

int main(int argc, char** argv) {

    // Point to null if no file argument, otherwise allocate a new CryptoG object.
    CryptoG* cryptographic_data = (argc == 1) ? nullptr : new CryptoG();

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