#include "FictionBook.h"

#include <stdexcept>

FictionBook::FictionBook(
    int id,
    const std::string& title,
    const std::vector<int>& authorIds,
    int publisherId,
    const std::string& topic,
    const std::string& location,
    const std::string& genre
)
    : id(id),
      title(title),
      authorIds(authorIds),
      publisherId(publisherId),
      topic(topic),
      location(location),
      genre(genre) {
    if (id <= 0) {
        throw std::invalid_argument("ID книги должен быть положительным");
    }
}

int FictionBook::getId() const {
    return id;
}

const std::string& FictionBook::getTitle() const {
    return title;
}

const std::vector<int>& FictionBook::getAuthorIds() const {
    return authorIds;
}

int FictionBook::getPublisherId() const {
    return publisherId;
}

const std::string& FictionBook::getTopic() const {
    return topic;
}

const std::string& FictionBook::getLocation() const {
    return location;
}

const std::string& FictionBook::getGenre() const {
    return genre;
}

std::string FictionBook::getInfo() const {
    return "Художественная книга: " + title
        + "\nID: " + std::to_string(id)
        + "\nТематика: " + topic
        + "\nРасположение: " + location
        + "\nЖанр: " + genre;
}
