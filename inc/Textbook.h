#pragma once

#include "Book.h"

/** @brief Учебник. */
class Textbook : public Book {
private:
    const int id;
    const std::string title;
    const std::vector<int> authorIds;
    const int publisherId;
    const std::string topic;
    const std::string location;
    const std::string subject;

public:
    /**
     * @brief Создаёт учебник.
     * @param id Положительный ID книги.
     * @param title Название.
     * @param authorIds ID авторов.
     * @param publisherId ID издательства.
     * @param topic Тематика.
     * @param location Расположение.
     * @param subject Учебный предмет.
     */
    Textbook(
        int id,
        const std::string& title,
        const std::vector<int>& authorIds,
        int publisherId,
        const std::string& topic,
        const std::string& location,
        const std::string& subject
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

    /** @brief Возвращает учебный предмет. */
    const std::string& getSubject() const;

    /** @brief Возвращает описание учебника. */
    std::string getInfo() const override;
};
