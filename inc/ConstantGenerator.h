#pragma once

#include "Generator.hpp"

/**
 * @brief Генератор, возвращающий одно и то же значение
 * 
 * Используется для заполнения матрицы нулями или константой.
 * При каждом вызове generate() возвращает значение,
 * заданное при создании объекта.
 */
class ConstantGenerator : public Generator
{
private:
    int constantValue;  ///< Значение, возвращаемое при каждом вызове

public:
    /**
     * @brief Конструктор константного генератора
     * 
     * @param value значение для возврата (по умолчанию 0)
     */
    ConstantGenerator(int value = 0);

    /**
     * @brief Вернуть константное значение
     * 
     * @return значение, заданное при создании объекта
     */
    int generate() override;
};
