#pragma once

#include "Exercise.hpp"

/**
 * @brief Задание 1 (вариант 12)
 * 
 * Заменить элемент, кратный трем, каждого столбца нулем.
 * 
 * Алгоритм:
 * - Проход по всем элементам матрицы
 * - Если matrix[i][j] % 3 == 0, то matrix[i][j] = 0
 * 
 * Пример: матрица [3, 4, 6] превратится в [0, 4, 0]
 */
class Task1 : public Exercise
{
public:
    /**
     * @brief Конструктор задания 1
     * 
     * @param matrix исходная матрица
     * @param generator указатель на генератор
     */
    Task1(const Matrix<int>& matrix, Generator* generator);

    /**
     * @brief Выполнить задание: заменить кратные 3 элементы на 0
     */
    void solve() override;
};
