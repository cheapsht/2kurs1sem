#include "Textbook.h"
#include <vector>
#include <string>

Textbook::Textbook(
    const std::string& title,
    const std::vector<Author>& authors,
    const Publisher& publisher,
    const std::string& topic,
    const std::string& location,
    const std::string& subject
)
       : Book(title, publisher, topic, location),
      authors(authors),subject(subject) {
}

std::string Textbook::getSubject() const {
    return subject;
}

std::string Textbook::getInfo() const {
    std::string info = "Учебник: " + getTitle();

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
    info += "\nПредмет: " + subject;

    return info;
}
const std::vector<Author>& Textbook::getAuthors() const {
    return authors;
}
