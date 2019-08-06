#include "entry.h"

void Entry::print_single_entry() const {
    std::cout << title << " " << username << " " << password << std::endl;
}