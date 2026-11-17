#include "LibraryCatalog.h"

#include <algorithm>
#include <stdexcept>

void LibraryCatalog::addAuthor(const Author& author) {
    for (const auto& existing : authors) {
        if (existing.getId() == author.getId()) {
            throw std::invalid_argument("ID автора уже существует");
        }
    }

    authors.push_back(author);
}

void LibraryCatalog::addPublisher(const Publisher& publisher) {
    for (const auto& existing : publishers) {
        if (existing.getId() == publisher.getId()) {
            throw std::invalid_argument("ID издательства уже существует");
        }
    }

    publishers.push_back(publisher);
}

void LibraryCatalog::validateBook(const Book& book) const {
    for (int id : getBookIds()) {
        if (id == book.getId()) {
            throw std::invalid_argument("ID книги уже существует");
        }
    }

    // Если издательства нет, метод выбросит исключение.
    findPublisherById(book.getPublisherId());

    // Проверяем существование каждого автора и отсутствие повторов.
    std::vector<int> checkedIds;

    for (int authorId : book.getAuthorIds()) {
        findAuthorById(authorId);

        if (std::find(
                checkedIds.begin(),
                checkedIds.end(),
                authorId
            ) != checkedIds.end()) {
            throw std::invalid_argument("Автор книги указан повторно");
        }

        checkedIds.push_back(authorId);
    }
}

void LibraryCatalog::addTextbook(const Textbook& textbook) {
    validateBook(textbook);
    textbooks.push_back(textbook);
}

void LibraryCatalog::addFictionBook(const FictionBook& book) {
    validateBook(book);
    fictionBooks.push_back(book);
}

const std::vector<Author>& LibraryCatalog::getAuthors() const {
    return authors;
}

const std::vector<Publisher>& LibraryCatalog::getPublishers() const {
    return publishers;
}

const std::vector<Textbook>& LibraryCatalog::getTextbooks() const {
    return textbooks;
}

const std::vector<FictionBook>& LibraryCatalog::getFictionBooks() const {
    return fictionBooks;
}

const Author& LibraryCatalog::findAuthorById(const int id) const {
    for (const auto& author : authors) {
        if (author.getId() == id) {
            return author;
        }
    }

    throw std::out_of_range("Автор не найден");
}

const Publisher& LibraryCatalog::findPublisherById(const int id) const {
    for (const auto& publisher : publishers) {
        if (publisher.getId() == id) {
            return publisher;
        }
    }

    throw std::out_of_range("Издательство не найдено");
}

const Book& LibraryCatalog::findBookById(const int id) const {
    for (const auto& textbook : textbooks) {
        if (textbook.getId() == id) {
            return textbook;
        }
    }

    for (const auto& book : fictionBooks) {
        if (book.getId() == id) {
            return book;
        }
    }

    throw std::out_of_range("Книга не найдена");
}

std::vector<int> LibraryCatalog::getBookIds() const {
    std::vector<int> result;

    for (const auto& textbook : textbooks) {
        result.push_back(textbook.getId());
    }

    for (const auto& book : fictionBooks) {
        result.push_back(book.getId());
    }

    return result;
}

std::vector<int> LibraryCatalog::findByTitle(
    const std::string& title
) const {
    std::vector<int> result;

    for (int id : getBookIds()) {
        if (findBookById(id).getTitle() == title) {
            result.push_back(id);
        }
    }

    return result;
}

std::vector<int> LibraryCatalog::findByAuthor(const int authorId) const {
    std::vector<int> result;

    for (int id : getBookIds()) {
        const auto& ids = findBookById(id).getAuthorIds();

        if (std::find(ids.begin(), ids.end(), authorId) != ids.end()) {
            result.push_back(id);
        }
    }

    return result;
}

std::vector<int> LibraryCatalog::findByTopic(
    const std::string& topic
) const {
    std::vector<int> result;

    for (int id : getBookIds()) {
        if (findBookById(id).getTopic() == topic) {
            result.push_back(id);
        }
    }

    return result;
}

std::vector<int> LibraryCatalog::findByPublisher(
    const std::string& name
) const {
    std::vector<int> result;

    for (int id : getBookIds()) {
        const Book& book = findBookById(id);

        const Publisher& publisher =
            findPublisherById(book.getPublisherId());

        if (publisher.getName() == name) {
            result.push_back(id);
        }
    }

    return result;
}

const std::string& LibraryCatalog::getLocation(const int bookId) const {
    return findBookById(bookId).getLocation();
}

std::string LibraryCatalog::getBookInfo(const int bookId) const {
    const Book& book = findBookById(bookId);

    std::string info = book.getInfo();
    info += "\nАвторы: ";

    const auto& ids = book.getAuthorIds();

    for (std::size_t i = 0; i < ids.size(); ++i) {
        if (i > 0) {
            info += "; ";
        }

        info += findAuthorById(ids[i]).getInfo();
    }

    info += "\nИздательство: ";
    info += findPublisherById(book.getPublisherId()).getName();

    return info;
}
