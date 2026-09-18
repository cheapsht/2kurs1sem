#pragma once

#include "Generator.h"
#include <iostream>

/**
 * @brief Генератор, читающий значения из входного потока
 * 
 * При каждом вызове generate() читает одно значение из потока.
 * По умолчанию читает из std::cin (клавиатура).
 * Позволяет подменить поток (например, для тестирования через std::istringstream).
 */
class IStreamGenerator : public Generator
{
private:
    std::istream& in;  ///< Ссылка на входной поток

public:
    /**
     * @brief Конструктор генератора из потока
     * 
     * @param in входной поток (по умолчанию std::cin)
     */
    IStreamGenerator(std::istream& in = std::cin);

    /**
     * @brief Прочитать следующее значение из потока
     * 
     * Если поток пуст или некорректен, возвращает 0.
     * 
     * @return следующее целое число из потока
     */
    int generate() override;
};
