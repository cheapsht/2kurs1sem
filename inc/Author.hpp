#pragma once

#include <string>

class Author {
private:
    const std::string fullName;

public:
    explicit Author(const std::string& fullName);

    std::string getFullName() const;
};
