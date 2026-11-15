#pragma once

#include <string>
#include <vector>

#include "Author.h"
#include "Publisher.h"
#include "Textbook.h"
#include "FictionBook.h"

/** @brief Хранит объекты отдельно и связывает их по ID. */
class LibraryCatalog {
private:
    std::vector<Author> authors;
    std::vector<Publisher> publishers;
    std::vector<Textbook> textbooks;
    std::vector<FictionBook> fictionBooks;

    /** @brief Проверяет уникальность ID и существование связей книги. */
    void validateBook(const Book& book) const;

public:
    /** @brief Добавляет автора с уникальным ID. */
    void addAuthor(const Author& author);

    /** @brief Добавляет издательство с уникальным ID. */
    void addPublisher(const Publisher& publisher);

    /** @brief Добавляет учебник после проверки связей. */
    void addTextbook(const Textbook& textbook);

    /** @brief Добавляет художественную книгу после проверки связей. */
    void addFictionBook(const FictionBook& book);

    /** @brief Возвращает авторов каталога. */
    const std::vector<Author>& getAuthors() const;

    /** @brief Возвращает издательства каталога. */
    const std::vector<Publisher>& getPublishers() const;

    /** @brief Возвращает учебники каталога. */
    const std::vector<Textbook>& getTextbooks() const;

    /** @brief Возвращает художественные книги каталога. */
    const std::vector<FictionBook>& getFictionBooks() const;

    /**
     * @brief Находит автора по ID.
     * @throws std::out_of_range Если автор не найден.
     */
    const Author& findAuthorById(int id) const;

    /**
     * @brief Находит издательство по ID.
     * @throws std::out_of_range Если издательство не найдено.
     */
    const Publisher& findPublisherById(int id) const;

    /**
     * @brief Находит книгу любого вида по ID.
     * @throws std::out_of_range Если книга не найдена.
     */
    const Book& findBookById(int id) const;

    /** @brief Возвращает ID всех книг каталога. */
    std::vector<int> getBookIds() const;

    /** @brief Возвращает ID книг с точным названием. */
    std::vector<int> findByTitle(const std::string& title) const;

    /** @brief Возвращает ID книг автора, включая соавторство. */
    std::vector<int> findByAuthor(int authorId) const;

    /** @brief Возвращает ID книг с точной тематикой. */
    std::vector<int> findByTopic(const std::string& topic) const;

    /** @brief Возвращает ID книг издательств с указанным названием. */
    std::vector<int> findByPublisher(const std::string& name) const;

    /** @brief Возвращает расположение книги по ID. */
    const std::string& getLocation(int bookId) const;

    /** @brief Возвращает описание с ФИО авторов и названием издательства. */
    std::string getBookInfo(int bookId) const;
};
