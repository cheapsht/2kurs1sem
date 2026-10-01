#pragma once

#include "Matrix.hpp"
#include "Generator.hpp"

/**
 * @brief Абстрактный базовый класс для заданий над матрицей
 */
class Exercise
{
protected:
    Matrix<int> matrix;   ///< Рабочая копия матрицы
    Generator* generator; ///< Указатель на генератор (не владеет объектом)

public:
    /**
     * @brief Конструктор задания
     * @param matrix исходная матрица
     * @param generator указатель на генератор
     */
    Exercise(const Matrix<int>& matrix, Generator* generator);

    /**
     * @brief Виртуальный деструктор
     * @note Используем = default, так как специальная очистка не требуется
     */
    virtual ~Exercise() = default; 

    /**
     * @brief Решить задание (изменить матрицу)
     * @note Чисто виртуальный метод
     */
    virtual void solve() = 0;

    /**
     * @brief Получить текущее состояние матрицы
     * @return копия матрицы после выполнения задания
     */
    Matrix<int> getMatrix() const;
};
