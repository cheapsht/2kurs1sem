#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Book.h"

/**
 * @brief Хранит книги и выполняет поиск.
 */
class LibraryCatalog {
private:
    /** @brief Книги каталога. */
    std::vector<std::unique_ptr<Book>> books;

public:
    /**
     * @brief Добавляет книгу, передавая владение каталогу.
     * @param book Указатель на книгу.
     * @throws std::invalid_argument Если указатель пустой.
     */
    void addBook(std::unique_ptr<Book> book);

    /**
     * @brief Возвращает все книги каталога.
     * @return Список указателей на книги.
     */
    std::vector<const Book*> getBooks() const;

    /**
     * @brief Ищет книги по точному названию.
     * @param title Название.
     * @return Найденные книги или пустой список.
     */
    std::vector<const Book*> findByTitle(
        const std::string& title
    ) const;

    /**
     * @brief Ищет книги автора, включая соавторство.
     * @param authorId ID автора.
     * @return Найденные книги или пустой список.
     */
    std::vector<const Book*> findByAuthor(int authorId) const;

    /**
     * @brief Ищет книги по точной тематике.
     * @param topic Тематика.
     * @return Найденные книги или пустой список.
     */
    std::vector<const Book*> findByTopic(
        const std::string& topic
    ) const;

    /**
     * @brief Ищет книги указанного издательства.
     * @param publisherName Точное название издательства.
     * @return Найденные книги или пустой список.
     */
    std::vector<const Book*> findByPublisher(
        const std::string& publisherName
    ) const;
};
