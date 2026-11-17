#pragma once

#include <string>

/** @brief Издательство. */
class Publisher {
private:
    const int id;
    const std::string name;

public:
    /**
     * @brief Создаёт издательство.
     * @param id Положительный ID.
     * @param name Название.
     */
    Publisher(int id, const std::string& name);

    /** @brief Возвращает ID издательства. */
    int getId() const;

    /** @brief Возвращает название издательства. */
    const std::string& getName() const;
};
