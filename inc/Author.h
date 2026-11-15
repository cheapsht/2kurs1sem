#pragma once

#include <string>

/** @brief Автор книги. */
class Author {
private:
    const int id;
    const std::string fullName;

public:
    /**
     * @brief Создаёт автора.
     * @param id Положительный ID.
     * @param fullName ФИО автора.
     */
    Author(int id, const std::string& fullName);

    /** @brief Возвращает ID автора. */
    int getId() const;

    /** @brief Возвращает ФИО автора. */
    const std::string& getFullName() const;

    /** @brief Возвращает ID и ФИО через запятую. */
    std::string getInfo() const;
};
