#pragma once

#include "Book.h"

/** @brief Художественная книга. */
class FictionBook : public Book {
private:
    const int id;
    const std::string title;
    const std::vector<int> authorIds;
    const int publisherId;
    const std::string topic;
    const std::string location;
    const std::string genre;

public:
    /**
     * @brief Создаёт художественную книгу.
     * @param id Положительный ID книги.
     * @param title Название.
     * @param authorIds ID авторов.
     * @param publisherId ID издательства.
     * @param topic Тематика.
     * @param location Расположение.
     * @param genre Жанр.
     */
    FictionBook(
        int id,
        const std::string& title,
        const std::vector<int>& authorIds,
        int publisherId,
        const std::string& topic,
        const std::string& location,
        const std::string& genre
    );

    /** @brief Возвращает ID книги. */
    int getId() const override;

    /** @brief Возвращает название. */
    const std::string& getTitle() const override;

    /** @brief Возвращает ID авторов. */
    const std::vector<int>& getAuthorIds() const override;

    /** @brief Возвращает ID издательства. */
    int getPublisherId() const override;

    /** @brief Возвращает тематику. */
    const std::string& getTopic() const override;

    /** @brief Возвращает расположение. */
    const std::string& getLocation() const override;

    /** @brief Возвращает жанр. */
    const std::string& getGenre() const;

    /** @brief Возвращает описание книги. */
    std::string getInfo() const override;
};
