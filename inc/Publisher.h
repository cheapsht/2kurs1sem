#pragma once

#include <string>

class Publisher {
private:
    const std::string name;

public:
    explicit Publisher(const std::string& name);

    std::string getName() const;
};
