#include "FictionBook.h"

#include <cstddef>
#include <string>
#include <vector>

FictionBook::FictionBook(
    const std::string& title,
    const std::vector<Author>& authors,
    const Publisher& publisher,
    const std::string& topic,
    const std::string& location,
    const std::string& genre
)
     : Book(title, publisher, topic, location),
      authors(authors),genre(genre) {
}

std::string FictionBook::getGenre() const {
    return genre;
}

std::string FictionBook::getInfo() const {
    std::string info = "Художественная книга: " + getTitle();

    info += "\nАвторы: ";

    const auto& authors = getAuthors();

    for (std::size_t i = 0; i < authors.size(); ++i) {
        if (i > 0) {
            info += "; ";
        }

        info += authors[i].getInfo();
    }

    info += "\nИздательство: " + getPublisher().getName();
    info += "\nТематика: " + getTopic();
    info += "\nРасположение: " + getLocation();
    info += "\nЖанр: " + genre;

    return info;
}
const std::vector<Author>& FictionBook::getAuthors() const {
    return authors;
}
