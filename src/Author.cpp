#include "Author.h"

Author::Author(const std::string& fullName)
    : fullName(fullName) {
}

std::string Author::getFullName() const {
    return fullName;
}
