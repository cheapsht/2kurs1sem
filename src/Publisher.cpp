#include "Publisher.h"

Publisher::Publisher(const std::string& name)
    : name(name) {
}

std::string Publisher::getName() const {
    return name;
}
