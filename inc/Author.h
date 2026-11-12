#pragma once

#include <string>

class Author {
private:
    const int id;
    const std::string fullName;

public:
    explicit Author(int id, const std::string& fullName);

    std::string getInfo() const;
};
