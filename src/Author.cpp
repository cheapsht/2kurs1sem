#include "Author.h"

#include <stdexcept>

Author::Author(int id, const std::string& fullName)
    : id(id), fullName(fullName) {
    if (id <= 0) {
        throw std::invalid_argument("ID автора должен быть положительным");
    }
}

int Author::getId() const {
    return id;
}

const std::string& Author::getFullName() const {
    return fullName;
}

std::string Author::getInfo() const {
    return std::to_string(id) + ", " + fullName;
}
