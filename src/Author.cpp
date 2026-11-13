#include "Author.h"

Author::Author(int id, const std::string& fullName)
    : id(id), fullName(fullName) {
}

std::string Author::getInfo() const 
{
    return std::to_string(id) + ", " + fullName;
}
int Author::getId() const 
{
    return id;
}
