#include "utils.h"

void print_byte_array_as_decimal(const unsigned char* str, const size_t length) {
        
        std::cout << "[  ";
        for (int i = 0; i < length; i++) {
            std::cout << std::dec << (int)str[i] << "  ";
        }
        std::cout << "]" << std::endl;
}