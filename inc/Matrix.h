#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

/**
 * @brief Шаблонный класс двумерной матрицы
 *
 * Хранит данные в std::vector<std::vector<T>>.
 * Поддерживает ввод/вывод, доступ по индексу, копирование.
 *
 * @tparam T тип элементов (int, double и т.д.)
 */
template <typename T>
class Matrix
{
private:
    std::vector<std::vector<T>> data;  ///< Двумерный массив данных
    size_t rows_count;                  ///< Количество строк
    size_t cols_count;                  ///< Количество столбцов

public:
    /** @brief Пустая матрица 0x0 */
    Matrix();

    /**
     * @brief Матрица заданного размера
     * @param rows число строк
     * @param cols число столбцов
     */
    Matrix(size_t rows, size_t cols);

    /**
     * @brief Матрица заданного размера, заполненная значением
     * @param rows число строк
     * @param cols число столбцов
     * @param value значение для заполнения
     */
    Matrix(size_t rows, size_t cols, const T& value);

    /** @brief Конструктор копирования */
    Matrix(const Matrix& other);

    /** @brief Деструктор */
    ~Matrix();

    /** @brief Оператор присваивания */
    Matrix& operator=(const Matrix& other);

    /** @brief Доступ к строке по индексу (для чтения/записи) */
    std::vector<T>& operator[](size_t row);

    /** @brief Доступ к строке по индексу (только чтение) */
    const std::vector<T>& operator[](size_t row) const;

    /** @return число строк */
    size_t rows() const;

    /** @return число столбцов */
    size_t cols() const;

    /** @return строковое представление матрицы */
    std::string toString() const;

    /** @brief Заполнить всю матрицу значением */
    void fill(const T& value);

    /** @brief Заполнить нулями (или значением по умолчанию для типа T) */
    void fillZero();

    /** @brief Изменить размеры матрицы */
    void resize(size_t rows, size_t cols);

    /** @brief Вывод матрицы в поток (cout << matrix) */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& matrix);

    /** @brief Ввод матрицы из потока (cin >> matrix) */
    template <typename U>
    friend std::istream& operator>>(std::istream& in, Matrix<U>& matrix);
};
template <typename T>
Matrix<T>::Matrix() : rows_count(0), cols_count(0) {}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : rows_count(rows), cols_count(cols), data(rows, std::vector<T>(cols)) {}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T& value)
    : rows_count(rows), cols_count(cols), data(rows, std::vector<T>(cols, value)) {}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_count(other.rows_count), cols_count(other.cols_count), data(other.data) {}

template <typename T>
Matrix<T>::~Matrix() {}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
    if (this != &other) {
        this->rows_count = other.rows_count;
        this->cols_count = other.cols_count;
        this->data = other.data;
    }
    return *this;
}

template <typename T>
std::vector<T>& Matrix<T>::operator[](size_t row) {
    return data[row];
}

template <typename T>
const std::vector<T>& Matrix<T>::operator[](size_t row) const {
    return data[row];
}

template <typename T>
size_t Matrix<T>::rows() const {
    return rows_count;
}

template <typename T>
size_t Matrix<T>::cols() const {
    return cols_count;
}

template <typename T>
std::string Matrix<T>::toString() const {
    std::stringstream ss;
    for (size_t i = 0; i < rows_count; ++i) {
        for (size_t j = 0; j < cols_count; ++j) {
            ss << data[i][j] << "\t";
        }
        ss << "\n";
    }
    return ss.str();
}

template <typename T>
void Matrix<T>::fill(const T& value) {
    for (size_t i = 0; i < rows_count; ++i)
        for (size_t j = 0; j < cols_count; ++j)
            data[i][j] = value;
}

template <typename T>
void Matrix<T>::fillZero() {
    fill(T{});
}

template <typename T>
void Matrix<T>::resize(size_t rows, size_t cols) {
    rows_count = rows;
    cols_count = cols;
    data.resize(rows, std::vector<T>(cols));
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    out << matrix.toString();
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows_count; ++i)
        for (size_t j = 0; j < matrix.cols_count; ++j)
            in >> matrix.data[i][j];
    return in;
}
