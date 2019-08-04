#include <iostream>
#include <fstream>
#include <vector>
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/osrng.h"
#include "cryptopp/files.h"

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
    public:
    SecByteBlock key;
    SecByteBlock iv;
    const byte* plaintext;

    SecByteBlock generate_initialisation_vector() {
        AutoSeededRandomPool rnd;

        SecByteBlock iv(AES::BLOCKSIZE);
        rnd.GenerateBlock(iv, iv.size());
        return iv;
    }

    SecByteBlock generate_secure_key() {
      
        byte* key_buffer = (byte*)"masterpassword0";
        //std::cout << "Please enter your master password: ";
        //std::cin.getline((char*)key_buffer, AES::BLOCKSIZE); // This will ignore anything longer
      
        // The key has the correct length and can be initialised
        SecByteBlock key(key_buffer, AES::DEFAULT_KEYLENGTH);
        return key;
    }   

    // Constructor for case where no file is present
    CD (byte* str) {
        iv = generate_initialisation_vector();
        key = generate_secure_key();
        plaintext = str;
    }
    
    // Constructor for case where file is present
    CD () {
        key = generate_secure_key(); // Set key

        FileSource fs("database", false /* Do not pump all pumps immediately*/);

        SecByteBlock iv_buf(AES::BLOCKSIZE); // Set up a buffer to store the IV read from file
        ArraySink as(iv_buf, iv_buf.size()); // An ArraySink will handle writing data to iv_buf
        fs.Attach(new Redirector(as));       // Attaches the file object to our ArraySink
        fs.Pump(AES::BLOCKSIZE);             // Extract the first 16 bytes for the IV
        iv = iv_buf;                         // Set iv

        
        // decryptor is of type StreamTransformationFilter
        CFB_Mode<AES>::Decryption decryptor(key, key.size(), iv);
        ByteQueue queue;
        
        // Detach deletes the current attachment, meaning it frees the memory
        // associated with the "as" ArraySink above.
        fs.Detach(new StreamTransformationFilter(decryptor, new Redirector(queue)));
        fs.PumpAll(); // Pump the remaining bytes from the file through the decryptor and into the queue.
        
        SecByteBlock data_buf(queue.MaxRetrievable());
        ArraySink sink(data_buf, data_buf.size());
        queue.TransferTo(sink);

        plaintext = data_buf; // Set plaintext
    }

    void encrypt_and_write_to_file() {

        CFB_Mode<AES>::Encryption encryptor(key, key.size(), iv);

        FileSink output_file("database", true);
        
        ArraySource write_iv(iv, 
                             iv.size(), 
                             true, 
                             new Redirector(output_file)); // Stream the bytes held by iv into the file sink
        
        ArraySource write_data(plaintext,
                               std::strlen((char*)plaintext), 
                               true, 
                               new StreamTransformationFilter(encryptor, new Redirector(output_file)));
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