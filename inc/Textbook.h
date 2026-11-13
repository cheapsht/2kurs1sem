#pragma once
#include <vector>
#include <string>
#include "Book.h"

class Textbook : public Book {
private:
    const std::string subject;

public:
    Textbook(
        const std::string& title,
        const std::vector<Author>& authors,
        const Publisher& publisher,
        const std::string& topic,
        const std::string& location,
        const std::string& subject
    );

    std::string getSubject() const;

    std::string getInfo() const override;
};
