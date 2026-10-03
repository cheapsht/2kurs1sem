#pragma once

#include "Generator.hpp"
#include <random>

/**
 * @brief Генератор случайных целых чисел в диапазоне [min, max]
 */
class RandomGenerator : public Generator
{
private:
    std::uniform_int_distribution<int> distribution;  ///< Распределение значений в диапазоне
    std::mt19937 generator;                            ///< Генератор псевдослучайных чисел

public:
    /**
     * @brief Конструктор генератора случайных чисел
     * 
     * Инициализирует генератор аппаратным случайным числом
     * (std::random_device) и настраивает диапазон значений.
     * 
     * @param min минимальное значение (включительно)
     * @param max максимальное значение (включительно)
     */
    RandomGenerator(const int min, const int max);

    /**
     * @brief Сгенерировать следующее случайное число
     * 
     * @return случайное целое число из диапазона [min, max]
     */
    int generate() override;
};
