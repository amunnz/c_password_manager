#include <iostream>
#include <fstream>
#include <vector>
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/osrng.h"

using namespace CryptoPP;

void print_byte_array_as_decimal(const unsigned char* str);

class Entry {
    std::string title;
    std::string username;
    std::string password;
};


// iv is formed by either 1) generating randomly or 2) reading from end of file
// key is formed by user input of a string
class CD {
    private:
    SecByteBlock key;
    SecByteBlock iv;
    byte* plaintext;
    byte* ciphertext;

    SecByteBlock generate_initialisation_vector() {
        AutoSeededRandomPool rnd;

        SecByteBlock iv(AES::BLOCKSIZE);
        rnd.GenerateBlock(iv, iv.size());
        return iv;
    }

    SecByteBlock generate_secure_key(std::string string_key) {

        // The key is too long
        if (string_key.length() > AES::BLOCKSIZE) {
            std::cout << "The key is too long. Please enter a key with maximum " << AES::BLOCKSIZE << " characters." << std::endl;
            std::cout << "Aborting..." << std::endl;
            exit(1);
        // The key is too short and must be padded with zeroes
        } else if (string_key.length() < AES::BLOCKSIZE) {
            string_key.append(AES::BLOCKSIZE - string_key.length(), '0');
        }
        
        // The key has the correct length and can be initialised
        SecByteBlock key((const byte*)string_key.data(), string_key.size());
        return key;
    }   

    // Constructor for use when the initialisation vector must be generated (new database)
    public:
    CD (std::string string_key, std::string str) {
        iv = generate_initialisation_vector();
        key = generate_secure_key(string_key);
        plaintext = (byte*)str.data();
        ciphertext = nullptr;
    }

    void encrypt() {
        size_t message_length = std::strlen((char *) plaintext);

        byte buffer[1000];
                
        CFB_Mode<AES>::Encryption encryptor(key, key.size(), iv);
        encryptor.ProcessData(buffer, plaintext, message_length);

        // Repoint ciphertext to the data held in buffer
        ciphertext = buffer;
    }

    void decrypt() {
        // We don't know how big the database is, so give it plenty of space:
        size_t message_length = 1000;

        byte buffer[1000];
        
        CFB_Mode<AES>::Decryption decryptor(key, key.size(), iv);       
        decryptor.ProcessData(buffer, ciphertext, message_length);

        std::cout << "Decrypted data: " << buffer << std::endl;
    }

    // void writeToFile() {
    //     //To Do
    //     //  -Add IV vector to the end of the data string
    //     std::ofstream fs("./key.bin", std::ios::binary);
    //     std::cout << sizeof(data) << std::endl;
    //     std::string s((char*)data,sizeof(data));
    //     std::cout <<"running write to file" << std::endl;
    //     std::cout <<"Initial String: " << s << std::endl;

    //     std::string iv_string((char*)(byte*)iv, sizeof(iv));
    //     s.append(iv_string);
    //     std::cout <<"Appended String: " << s << std::endl;

    //     fs.write((char*)s.data(), s.size());
    // }

    // void readFile() {
    //     //To Do
    //     //  -Splt IV vector of the end of the data string
    //     print_byte_array_as_decimal(data);
    //     std::ifstream fs("./key.bin", std::ios::binary);
    //     //byte* data2;
    //     fs.read((char*)data, 100);
    //     print_byte_array_as_decimal(data);

    // }
};

void print_byte_array_as_decimal(const unsigned char* str) {
        const int length = strlen((char*)str);
        std::cout << "[  ";
        for (int i = 0; i < length; i++) {
            std::cout << (int)str[i] << "  ";
        }
        std::cout << "]" << std::endl;
}