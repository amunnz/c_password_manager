#include "utils.h"
#include <iostream>

void print_byte_array_as_decimal(const unsigned char* str) {
        const int length = strlen((char*)str);
        std::cout << "[  ";
        for (int i = 0; i < length; i++) {
            std::cout << (int)str[i] << "  ";
        }
        std::cout << "]" << std::endl;
}