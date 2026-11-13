#pragma once

#include <string>

/**
 * @brief Автор книги.
 */
class Author {
private:
    /** @brief Уникальный номер автора. */
    const int id;

    /** @brief ФИО автора. */
    const std::string fullName;

public:
    /**
     * @brief Создаёт автора.
     * @param id Уникальный номер.
     * @param fullName ФИО.
     */
    explicit Author(int id, const std::string& fullName);

    /**
     * @brief Возвращает сведения об авторе.
     * @return ID и ФИО через запятую.
     */
    std::string getInfo() const;
    /**
     * @brief Возвращает айди автора
     * @return ID через запятую
     */
    int getId() const;
};
