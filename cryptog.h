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

    SecByteBlock generate_secure_key() const;
    SecByteBlock generate_initialisation_vector() const;

    SecByteBlock read_iv_from_file(FileSource& fs) const;
    SecByteBlock read_and_decrypt_database_from_file(FileSource& fs) const;
    
    public:
    
    CryptoG(const std::string& str, const size_t length); // Constructor for case where no file is present
    CryptoG(FileSource& fs); // Constructor for case where file is present

    void encrypt_and_write_to_file() const;
};

#endif