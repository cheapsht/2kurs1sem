#pragma once

#include "Generator.hpp"
#include <iostream>

/**
 * @brief Генератор, читающий значения из входного потока
 *
 * По умолчанию читает из std::cin.
 * Позволяет подменить поток (например, для тестов).
 */
class IStreamGenerator : public Generator
{
private:
    std::istream& in;

public:
    /**
     * @brief Конструктор
     * @param in входной поток (по умолчанию std::cin)
     */
    IStreamGenerator(std::istream& in = std::cin);

    /** @brief Прочитать следующее значение из потока */
    int generate() override;
};
