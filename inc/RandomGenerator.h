#pragma once

#include "Generator.hpp"
#include <random>

/**
 * @brief Генератор случайных целых чисел в диапазоне [min, max]
 *
 * Использует std::mt19937 (генератор Мерсенна) и
 * равномерное распределение.
 */
class RandomGenerator : public Generator
{
private:
    std::uniform_int_distribution<int> distribution;  
    std::mt19937 generator;                          

public:
    /**
     * @brief Конструктор
     * @param min минимальное значение (включительно)
     * @param max максимальное значение (включительно)
     */
    RandomGenerator(const int min, const int max);

    /** @brief Вернуть следующее случайное число из диапазона */
    int generate() override;
};
