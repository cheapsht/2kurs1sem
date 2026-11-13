#include "LibraryCatalog.h"

#include <stdexcept>
#include <utility>

void LibraryCatalog::addBook(std::unique_ptr<Book> book) {
    if (!book) {
        throw std::invalid_argument("Нельзя добавить пустую книгу");
    }

    books.push_back(std::move(book));
}

std::vector<const Book*> LibraryCatalog::getBooks() const {
    std::vector<const Book*> result;

    for (const auto& book : books) {
        result.push_back(book.get());
    }

    return result;
}

std::vector<const Book*> LibraryCatalog::findByTitle(
    const std::string& title
) const {
    std::vector<const Book*> result;

    for (const auto& book : books) {
        if (book->getTitle() == title) {
            result.push_back(book.get());
        }
    }

    return result;
}

std::vector<const Book*> LibraryCatalog::findByAuthor(
    int authorId
) const {
    std::vector<const Book*> result;

    for (const auto& book : books) {
        for (const auto& author : book->getAuthors()) {
            if (author.getId() == authorId) {
                result.push_back(book.get());
                break;
            }
        }
    }

    return result;
}

std::vector<const Book*> LibraryCatalog::findByTopic(
    const std::string& topic
) const {
    std::vector<const Book*> result;

    for (const auto& book : books) {
        if (book->getTopic() == topic) {
            result.push_back(book.get());
        }
    }

    return result;
}

std::vector<const Book*> LibraryCatalog::findByPublisher(
    const std::string& publisherName
) const {
    std::vector<const Book*> result;

    for (const auto& book : books) {
        if (book->getPublisher().getName() == publisherName) {
            result.push_back(book.get());
        }
    }

    return result;
}
