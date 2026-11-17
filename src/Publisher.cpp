#include "Publisher.h"

#include <stdexcept>

Publisher::Publisher(int id, const std::string& name)
    : id(id), name(name) {
    if (id <= 0) {
        throw std::invalid_argument(
            "ID издательства должен быть положительным"
        );
    }
}

int Publisher::getId() const {
    return id;
}

const std::string& Publisher::getName() const {
    return name;
}
