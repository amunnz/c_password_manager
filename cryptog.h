#ifndef CRYPTOG_H
#define CRYPTOG_H

#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/osrng.h"
#include "cryptopp/files.h"

#include "utils.h"

using namespace CryptoPP;
// iv is formed by either 1) generating randomly or 2) reading from end of file
// key is formed by user input of a string
class CryptoG {
    private:
    SecByteBlock key;
    SecByteBlock iv;
    SecByteBlock plaintext;

    SecByteBlock generate_initialisation_vector();
    
    SecByteBlock generate_secure_key();

    public:
    
    CryptoG (byte* str); // Constructor for case where no file is present
    
    CryptoG (); // Constructor for case where file is present

    void encrypt_and_write_to_file();
};

#endif