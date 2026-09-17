#pragma once

#include "Exercise.hpp"

/**
 * @brief Задание 2 (вариант 12)
 *
 * Удалить все строки, в которых второй элемент больше предпоследнего.
 * Сравнение: matrix[i][1] > matrix[i][cols-2].
 * Проход снизу вверх, чтобы корректно удалять строки без сдвига индексов.
 */
class Task2 : public Exercise
{
public:
    /**
     * @brief Конструктор
     * @param matrix исходная матрица
     * @param generator указатель на генератор
     */
    Task2(const Matrix<int>& matrix, Generator* generator);

    /** @brief Удалить строки, где второй элемент больше предпоследнего */
    void solve() override;
};

