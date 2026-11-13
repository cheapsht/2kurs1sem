#pragma once

#include <string>

/**
 * @brief Издательство книги.
 */
class Publisher {
private:
    /** @brief Название издательства. */
    const std::string name;

public:
    /**
     * @brief Создаёт издательство.
     * @param name Название издательства.
     */
    explicit Publisher(const std::string& name);

    /**
     * @brief Возвращает название издательства.
     * @return Название.
     */
    std::string getName() const;
};
