#pragma once

#include "Matrix.hpp"
#include "Generator.hpp"

/**
 * @brief Абстрактный базовый класс для заданий над матрицей
 * 
 * Хранит копию матрицы и указатель на генератор.
 * Конкретные задания (Task1, Task2) реализуются в наследниках
 * через переопределение метода solve().
 */
class Exercise
{
protected:
    Matrix<int> matrix;   ///< Рабочая копия матрицы
    Generator* generator; ///< Указатель на генератор (не владеет объектом)

public:
    /**
     * @brief Конструктор задания
     * 
     * @param matrix исходная матрица (создается копия)
     * @param generator указатель на генератор
     */
    Exercise(const Matrix<int>& matrix, Generator* generator);

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Exercise();

    /**
     * @brief Решить задание (изменить матрицу)
     * 
     * Чисто виртуальный метод. Каждый наследник реализует
     * свою логику преобразования матрицы.
     */
    virtual void solve() = 0;

    /**
     * @brief Получить текущее состояние матрицы
     * 
     * @return копия матрицы после выполнения задания
     */
    Matrix<int> getMatrix() const;
};
