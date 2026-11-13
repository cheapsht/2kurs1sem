#include "Book.h"

Book::Book(
    const std::string& title,
    const Publisher& publisher,
    const std::string& topic,
    const std::string& location
)
    : title(title),
      publisher(publisher),
      topic(topic),
      location(location) {
}

const std::string& Book::getTitle() const {
    return title;
}
}

const Publisher& Book::getPublisher() const {
    return publisher;
}

const std::string& Book::getTopic() const {
    return topic;
}

const std::string& Book::getLocation() const {
    return location;
}
