#include "cryptog.h"

int main(int argc, char** argv) {
    
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    byte* message = (byte*)"Title,Username,Password\nFacebook,email@address.com,myfbpassword";

    // Assume there is a file to open with a iv and encrypted data
    //CD cryptographic_data = CD();

    // This should be done as late as possible.
    CryptoG cryptographic_data = CryptoG(message);
    cryptographic_data.encrypt_and_write_to_file();      
    
    return 0;
}