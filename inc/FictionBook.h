#pragma once

#include <string>
#include <vector>

#include "Book.h"

/**
 * @brief Художественная книга с указанием жанра.
 */
class FictionBook : public Book {
private:
    /** @brief Жанр книги. */
    const std::string genre;

public:
    /**
     * @brief Создаёт художественную книгу.
     * @param title Название.
     * @param authors Список авторов.
     * @param publisher Издательство.
     * @param topic Тематика.
     * @param location Стеллаж и полка.
     * @param genre Жанр.
     */
    FictionBook(
        const std::string& title,
        const std::vector<Author>& authors,
        const Publisher& publisher,
        const std::string& topic,
        const std::string& location,
        const std::string& genre
    );

    /**
     * @brief Возвращает жанр книги.
     * @return Название жанра.
     */
    std::string getGenre() const;

    /**
     * @brief Возвращает полную информацию о книге.
     * @return Строка с общими данными и жанром.
     */
    std::string getInfo() const override;
};
