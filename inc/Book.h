#pragma once

#include <string>
#include <vector>

/** @brief Абстрактный интерфейс книги без полей данных. */
class Book {
public:
    virtual ~Book() = default;

    /** @brief Возвращает ID книги. */
    virtual int getId() const = 0;

    /** @brief Возвращает название. */
    virtual const std::string& getTitle() const = 0;

    /** @brief Возвращает ID авторов. */
    virtual const std::vector<int>& getAuthorIds() const = 0;

    /** @brief Возвращает ID издательства. */
    virtual int getPublisherId() const = 0;

    /** @brief Возвращает тематику. */
    virtual const std::string& getTopic() const = 0;

    /** @brief Возвращает расположение. */
    virtual const std::string& getLocation() const = 0;

    /** @brief Возвращает описание книги. */
    virtual std::string getInfo() const = 0;
};
