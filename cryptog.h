#ifndef CRYPTOG_H
#define CRYPTOG_H

#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/osrng.h"
#include "cryptopp/files.h"

#include "utils.h"

using namespace CryptoPP;

class CryptoG {
    private:
    const SecByteBlock key;
    SecByteBlock iv;
    SecByteBlock plaintext;

    SecByteBlock generate_initialisation_vector();
    SecByteBlock generate_secure_key();

    void read_and_decrypt_file();
    
    public:
    
    CryptoG(const std::string& str, const size_t length); // Constructor for case where no file is present
    CryptoG(); // Constructor for case where file is present

    void encrypt_and_write_to_file() const;
};

#endif