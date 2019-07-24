#include <iostream>
#include <fstream>
#include <vector>
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/osrng.h"

class Entry {
    std::string title;
    std::string username;
    std::string password;
};


// iv is formed by either 1) generating randomly or 2) reading from end of file
// key is formed by user input of a string

class CD {
    private:
    CryptoPP::SecByteBlock key;
    CryptoPP::SecByteBlock iv;
    CryptoPP::byte* data;

    CryptoPP::SecByteBlock generate_initialisation_vector() {
        CryptoPP::AutoSeededRandomPool rnd;

        CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
        rnd.GenerateBlock(iv, iv.size());

        return iv;
    }

    CryptoPP::SecByteBlock generate_secure_key(std::string string_key) {

        // The key is too long
        if (string_key.length() > CryptoPP::AES::BLOCKSIZE) {
            std::cout << "The key is too long. Please enter a key with maximum " << CryptoPP::AES::BLOCKSIZE << " characters." << std::endl;
            std::cout << "Aborting..." << std::endl;
            exit(1);
        // The key is too short and must be padded with zeroes
        } else if (string_key.length() < CryptoPP::AES::BLOCKSIZE) {
            string_key.append(CryptoPP::AES::BLOCKSIZE - string_key.length(), '0');
        }
        
        // The key has the correct length and can be initialised
        CryptoPP::SecByteBlock key((const CryptoPP::byte*)string_key.data(), string_key.size());
        
        return key;
    }

    CryptoPP::byte* initialise_data(std::string str) {
        return (CryptoPP::byte*)str.data();
    }
    

    // Constructor for use when the initialisation vector must be generated (new database)
    public:
    CD (std::string string_key, std::string plaintext) {
        iv = generate_initialisation_vector();
        key = generate_secure_key(string_key);
        data = initialise_data(plaintext);
    }

    // void encrypt(std::string message, CryptoPP::byte* ciphertext) {
    //     size_t message_length = message.length();
           
    //     CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryptor(key, key.size(), iv);
    //     encryptor.ProcessData(ciphertext, (CryptoPP::byte*)message.data(), message_length);
    // }
    void encrypt() {
        size_t message_length = std::strlen((char *) data);
           
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryptor(key, key.size(), iv);
        encryptor.ProcessData(data, data, message_length);
    }

    // void decrypt(CryptoPP::byte* plaintext, CryptoPP::byte* ciphertext) {
    //     size_t message_length = std::strlen((char *)ciphertext);

    //     CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryptor(key, key.size(), iv);
    //     decryptor.ProcessData(plaintext, ciphertext, message_length);
        
    // }
    void decrypt() {
        size_t message_length = std::strlen((char *)data);

        CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryptor(key, key.size(), iv);
        decryptor.ProcessData(data, data, message_length);
        
        std::cout << data << std::endl;
    }
};

void print_byte_array_as_decimal(const unsigned char* str) {
        const int length = strlen((char*)str);
        std::cout << "[  ";
        for (int i = 0; i < length; i++) {
            std::cout << (int)str[i] << "  ";
        }
        std::cout << "]" << std::endl;
}