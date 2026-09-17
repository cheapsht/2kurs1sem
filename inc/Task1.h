#pragma once

#include "Exercise.hpp"

/**
 * @brief Задание 1 (вариант 12)
 *
 * Заменить элемент, кратный трём, каждого столбца нулём.
 * Проход по всем элементам матрицы: если matrix[i][j] % 3 == 0,
 * то matrix[i][j] = 0.
 */
class Task1 : public Exercise
{
public:
    /**
     * @brief Конструктор
     * @param matrix исходная матрица
     * @param generator указатель на генератор
     */
    Task1(const Matrix<int>& matrix, Generator* generator);

    /** @brief Выполнить замену элементов, кратных 3, на 0 */
    void solve() override;
};
