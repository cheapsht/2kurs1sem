#pragma once

#include "Matrix.hpp"
#include "Generator.hpp"

/**
 * @brief Абстрактный базовый класс для заданий над матрицей
 *
 * Хранит копию матрицы и указатель на генератор.
 * Конкретные задания реализуются в наследниках через метод solve().
 */
class Exercise
{
protected:
    Matrix<int> matrix;  
    Generator* generator; 

public:
    /**
     * @brief Конструктор
     * @param matrix исходная матрица
     * @param generator указатель на генератор
     */
    Exercise(const Matrix<int>& matrix, Generator* generator);

    /** @brief Деструктор */
    virtual ~Exercise();

    /** @brief Решить задание (изменить матрицу) */
    virtual void solve() = 0;

    Matrix<int> getMatrix() const;
};
