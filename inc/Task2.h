#pragma once

#include "Exercise.hpp"

/**
 * @brief Задание 2 (вариант 12)
 * 
 * Удалить все строки, в которых второй элемент больше предпоследнего.
 * 
 * Алгоритм:
 * - Для каждой строки сравниваем matrix[i][1] и matrix[i][cols-2]
 * - Если matrix[i][1] > matrix[i][cols-2], строка удаляется
 * - Проход выполняется снизу вверх для корректного удаления
 * 
 * Пример: строка [1, 5, 3, 2] удаляется (5 > 3),
 *         строка [1, 2, 5, 2] остается (2 <= 5)
 */
class Task2 : public Exercise
{
public:
    /**
     * @brief Конструктор задания 2
     * 
     * @param matrix исходная матрица
     * @param generator указатель на генератор
     */
    Task2(const Matrix<int>& matrix, Generator* generator);

    /**
     * @brief Выполнить задание: удалить строки по условию
     */
    void solve() override;
};
