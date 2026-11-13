#pragma once

#include <string>
#include <vector>

#include "Author.h"
#include "Publisher.h"

/**
 * @brief Абстрактный базовый класс книги.
 */
class Book {
private:
    /** @brief Название книги. */
    const std::string title;
    /** @brief Издательство книги. */
    const Publisher publisher;

    /** @brief Тематика книги. */
    const std::string topic;

    /** @brief Расположение книги в библиотеке. */
    const std::string location;

public:
    /**
     * @brief Задаёт общие данные книги.
     * @param title Название.
     * @param authors Список авторов.
     * @param publisher Издательство.
     * @param topic Тематика.
     * @param location Стеллаж и полка.
     */
    Book(
        const std::string& title,
        const Publisher& publisher,
        const std::string& topic,
        const std::string& location
    );

    /**
     * @brief Обеспечивает корректное удаление наследников через Book.
     */
    virtual ~Book() = default;

    /**
     * @brief Возвращает название книги.
     * @return Константная ссылка на название.
     */
    const std::string& getTitle() const;

    /**
     * @brief Возвращает авторов книги.
     * @return Константная ссылка на список авторов.
     */
    virtual const std::vector<Author>& getAuthors() const;

    /**
     * @brief Возвращает издательство книги.
     * @return Константная ссылка на издательство.
     */
    const Publisher& getPublisher() const;

    /**
     * @brief Возвращает тематику книги.
     * @return Константная ссылка на тематику.
     */
    const std::string& getTopic() const;

    /**
     * @brief Возвращает расположение книги.
     * @return Константная ссылка на расположение.
     */
    const std::string& getLocation() const;

    /**
     * @brief Возвращает описание книги; реализуется наследниками.
     * @return Строка с полной информацией о книге.
     */
    virtual std::string getInfo() const = 0;
};
