#pragma once

#include <string>
#include <vector>

#include "Author.h"
#include "Publisher.h"

class Book {
private:
    const std::string title;
    const std::vector<Author> authors;
    const Publisher publisher;
    const std::string topic;
    const std::string location;

public:
    Book(
        const std::string& title,
        const std::vector<Author>& authors,
        const Publisher& publisher,
        const std::string& topic,
        const std::string& location
    );

    virtual ~Book() = default;

    const std::string& getTitle() const;
    const std::vector<Author>& getAuthors() const;
    const Publisher& getPublisher() const;
    const std::string& getTopic() const;
    const std::string& getLocation() const;

    virtual std::string getInfo() const = 0;
};
