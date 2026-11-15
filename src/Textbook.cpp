#include "Textbook.h"

#include <stdexcept>

Textbook::Textbook(
    int id,
    const std::string& title,
    const std::vector<int>& authorIds,
    int publisherId,
    const std::string& topic,
    const std::string& location,
    const std::string& subject
)
    : id(id),
      title(title),
      authorIds(authorIds),
      publisherId(publisherId),
      topic(topic),
      location(location),
      subject(subject) {
    if (id <= 0) {
        throw std::invalid_argument("ID книги должен быть положительным");
    }
}

int Textbook::getId() const {
    return id;
}

const std::string& Textbook::getTitle() const {
    return title;
}

const std::vector<int>& Textbook::getAuthorIds() const {
    return authorIds;
}

int Textbook::getPublisherId() const {
    return publisherId;
}

const std::string& Textbook::getTopic() const {
    return topic;
}

const std::string& Textbook::getLocation() const {
    return location;
}

const std::string& Textbook::getSubject() const {
    return subject;
}

std::string Textbook::getInfo() const {
    return "Учебник: " + title
        + "\nID: " + std::to_string(id)
        + "\nТематика: " + topic
        + "\nРасположение: " + location
        + "\nПредмет: " + subject;
}
