#pragma once

#include <string>
#include <vector>

#include "Book.h"

/**
 * @brief Учебник с указанием учебного предмета.
 */
class Textbook : public Book {
private:
    /** @brief Учебный предмет. */
    const std::string subject;

public:
    /**
     * @brief Создаёт учебник.
     * @param title Название.
     * @param authors Список авторов.
     * @param publisher Издательство.
     * @param topic Тематика.
     * @param location Стеллаж и полка.
     * @param subject Учебный предмет.
     */
    Textbook(
        const std::string& title,
        const std::vector<Author>& authors,
        const Publisher& publisher,
        const std::string& topic,
        const std::string& location,
        const std::string& subject
    );

    /**
     * @brief Возвращает учебный предмет.
     * @return Название предмета.
     */
    std::string getSubject() const;

    /**
     * @brief Возвращает полную информацию об учебнике.
     * @return Строка с общими данными и учебным предметом.
     */
    std::string getInfo() const override;
};
