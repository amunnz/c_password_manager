#include "cryptog.h"

// Constructor for case where no file is present
CryptoG::CryptoG (const std::string& str, const size_t length)
    : key(generate_secure_key()),
      iv(generate_initialisation_vector()),
      plaintext(SecByteBlock((byte*)str.data(), length)) {}

// Constructor for case where file is present
CryptoG::CryptoG(FileSource& fs)
    : key(generate_secure_key()),
      iv(read_iv_from_file(fs)),
      plaintext(read_and_decrypt_database_from_file(fs)) {

    std::cout << "The decrypted file data reads:" << std::endl << plaintext.data() << std::endl;
}

SecByteBlock CryptoG::generate_secure_key() const {
    
    byte key_buffer[AES::MAX_KEYLENGTH] = { 0 };
    std::cout << "Please enter your master password: ";

    // getline makes the last char within the bounds of length
    // the null terminator, so in practice any byte after the
    // 31st is ignored.
    std::cin.getline((char*)key_buffer, AES::MAX_KEYLENGTH); 
    
    return SecByteBlock(key_buffer, AES::MAX_KEYLENGTH);
}   

SecByteBlock CryptoG::generate_initialisation_vector() const {
    AutoSeededRandomPool rnd;
    SecByteBlock iv_buf(AES::BLOCKSIZE);
    rnd.GenerateBlock(iv_buf, iv_buf.size());

    return iv_buf;
}

SecByteBlock CryptoG::read_iv_from_file(FileSource& fs) const {
    SecByteBlock iv_buf(AES::BLOCKSIZE); // Set up a buffer to store the IV read from file
    ArraySink as(iv_buf, iv_buf.size()); // An ArraySink will handle writing data to iv_buf
    fs.Attach(new Redirector(as));       // Attaches the file object to our ArraySink
    fs.Pump(AES::BLOCKSIZE);             // Extract the first 16 bytes for the IV

    return iv_buf;
}

SecByteBlock CryptoG::read_and_decrypt_database_from_file(FileSource& fs) const {
    CFB_Mode<AES>::Decryption decryptor(key, key.size(), iv);
    ByteQueue queue;
    
    // Detach old transformation and attach new one.
    fs.Detach(new StreamTransformationFilter(decryptor, new Redirector(queue)));
    fs.PumpAll(); // Pump the remaining bytes from the file through the decryptor and into the queue.
    
    SecByteBlock data_buf(queue.MaxRetrievable()); // Allocate buffer to fit exactly the number of bytes to be transferred.
    ArraySink sink(data_buf, data_buf.size());
    int bytes_transferred = queue.TransferTo(sink);

    return SecByteBlock(data_buf, bytes_transferred);
}

void CryptoG::encrypt_and_write_to_file() const {

    CFB_Mode<AES>::Encryption encryptor(key, key.size(), iv);

    FileSink output_file("database", true);
    
    ArraySource(iv, 
                iv.size(), 
                true, 
                new Redirector(output_file));
    
    ArraySource(plaintext.data(),
                plaintext.size(), 
                true, 
                new StreamTransformationFilter(encryptor, new Redirector(output_file)));
}