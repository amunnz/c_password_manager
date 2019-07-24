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
    byte* data;

    SecByteBlock generate_initialisation_vector() {
        //AutoSeededRandomPool rnd;

        std::string iv_string("0000000000000000");
        SecByteBlock iv((const byte*)iv_string.data(), iv_string.size());
        //SecByteBlock iv(AES::BLOCKSIZE);
        //rnd.GenerateBlock(iv, iv.size());

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


    //convert string to byte
    byte* initialise_data(std::string str) {
        return (byte*)str.data();
    }
    

    // Constructor for use when the initialisation vector must be generated (new database)
    public:
    CD (std::string string_key, std::string plaintext) {
        iv = generate_initialisation_vector();
        key = generate_secure_key(string_key);
        data = initialise_data(plaintext);
    }

    // void encrypt(std::string message, byte* ciphertext) {
    //     size_t message_length = message.length();
           
    //     CFB_Mode<AES>::Encryption encryptor(key, key.size(), iv);
    //     encryptor.ProcessData(ciphertext, (byte*)message.data(), message_length);
    // }
    void encrypt() {
        size_t message_length = std::strlen((char *) data);
           
        CFB_Mode<AES>::Encryption encryptor(key, key.size(), iv);
        encryptor.ProcessData(data, data, message_length);
    }

    // void decrypt(byte* plaintext, byte* ciphertext) {
    //     size_t message_length = std::strlen((char *)ciphertext);

    //     CFB_Mode<AES>::Decryption decryptor(key, key.size(), iv);
    //     decryptor.ProcessData(plaintext, ciphertext, message_length);
        
    // }
    void decrypt() {
        size_t message_length = std::strlen((char *)data);

        CFB_Mode<AES>::Decryption decryptor(key, key.size(), iv);
        decryptor.ProcessData(data, data, message_length);
        
        std::cout << data << std::endl;
    }

    void writeToFile() {
        //To Do
        //  -Add IV vector to the end of the data string
        std::ofstream fs("./key.bin", std::ios::binary);
        std::cout << sizeof(data) << std::endl;
        std::string s((char*)data,sizeof(data));
        std::cout <<"running write to file" << std::endl;
        std::cout <<"Initial String: " << s << std::endl;

        std::string iv_string((char*)(byte*)iv, sizeof(iv));
        s.append(iv_string);
        std::cout <<"Appended String: " << s << std::endl;

        fs.write((char*)s.data(), s.size());
    }

    void readFile() {
        //To Do
        //  -Splt IV vector of the end of the data string
        print_byte_array_as_decimal(data);
        std::ifstream fs("./key.bin", std::ios::binary);
        //byte* data2;
        fs.read((char*)data, 100);
        print_byte_array_as_decimal(data);

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