#include "cryptog.h"

SecByteBlock CryptoG::generate_initialisation_vector() {
    AutoSeededRandomPool rnd;

    SecByteBlock iv(AES::BLOCKSIZE);
    rnd.GenerateBlock(iv, iv.size());
    return iv;
}

SecByteBlock CryptoG::generate_secure_key() {
    
    byte key_buffer[AES::MAX_KEYLENGTH] = { 0 };
    std::cout << "Please enter your master password: ";

    // getline makes the last char within the bounds of length
    // the null terminator, so in practice any byte after the
    // 31st is ignored.
    std::cin.getline((char*)key_buffer, AES::MAX_KEYLENGTH); 
    
    return SecByteBlock(key_buffer, AES::MAX_KEYLENGTH);
}   

// Constructor for case where no file is present
CryptoG::CryptoG (const std::string& str, const size_t length)
    : key(generate_secure_key()),
      iv(generate_initialisation_vector()),
      plaintext(SecByteBlock((byte*)str.data(), length)) {}

// Constructor for case where file is present
CryptoG::CryptoG () : key(generate_secure_key()) {
    read_and_decrypt_file();
}
// TODO:
// Split this function up.
// In main, allocate a FileSource pointer
// Pass the pointer to the constructor
// Create two functions, which will return iv & plaintext respectively
// Use these two functions in the initialiser list of the above constructor
// to allow us to make them const.
void CryptoG::read_and_decrypt_file() {
    FileSource fs("database", false /* Do not pump all bytes immediately*/);

    SecByteBlock iv_buf(AES::BLOCKSIZE); // Set up a buffer to store the IV read from file
    ArraySink as(iv_buf, iv_buf.size()); // An ArraySink will handle writing data to iv_buf
    fs.Attach(new Redirector(as));       // Attaches the file object to our ArraySink
    fs.Pump(AES::BLOCKSIZE);             // Extract the first 16 bytes for the IV
    iv = iv_buf;                         // Set iv
    
    CFB_Mode<AES>::Decryption decryptor(key, key.size(), iv);
    ByteQueue queue;
    
    // Detach deletes the current attachment, meaning it frees the memory
    // associated with the "as" ArraySink above.
    fs.Detach(new StreamTransformationFilter(decryptor, new Redirector(queue)));
    fs.PumpAll(); // Pump the remaining bytes from the file through the decryptor and into the queue.
    
    SecByteBlock data_buf(queue.MaxRetrievable()); // Allocate buffer to fit exactly the number of bytes to be transferred.
    ArraySink sink(data_buf, data_buf.size());
    int bytes_transferred = queue.TransferTo(sink);

    plaintext = SecByteBlock(data_buf, bytes_transferred); // Set plaintext
    std::cout << "The decrypted file data reads:" << std::endl << plaintext.data() << std::endl;
}

void CryptoG::encrypt_and_write_to_file() {

    CFB_Mode<AES>::Encryption encryptor(key, key.size(), iv);

    FileSink output_file("database", true);
    
    ArraySource write_iv(   iv, 
                            iv.size(), 
                            true, 
                            new Redirector(output_file)); // Stream the bytes held by iv into the file sink
    
    ArraySource write_data( plaintext.data(),
                            plaintext.size(), 
                            true, 
                            new StreamTransformationFilter(encryptor, new Redirector(output_file)));
}