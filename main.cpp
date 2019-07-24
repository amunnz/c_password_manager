#include "password_manager.h"






int main(void) {
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    std::string message = "Title,Username,Password\nFacebook,email@address.com,myfbpassword";

    // The Cryptographic data object shouldn't be initialised/declared until we have
    // some kind of data ready to write to file in case 1)
    // In case 2), it will be initialised immediately after receiving user input for the password
    // To initialise it, we need a string holding the master password, optionally the IV read
    // from file in case 2), and either the encrypted data or plain text.
    std::string string_key = "master_password";
    CD cryptographic_data = CD(string_key, message);

    byte ciphertext[message.length()]; // Stores encrypted data

    cryptographic_data.encrypt(); // Encrypt

    cryptographic_data.writeToFile();
    cryptographic_data.readFile();
    // byte decrypted_data[message.length()]; // Stores decrytped data

    // cryptographic_data.decrypt(decrypted_data, ciphertext); // Decrypt
    cryptographic_data.decrypt();
    
    // std::cout << "Decrypted data: " << decrypted_data << std::endl;
    return 0;
}