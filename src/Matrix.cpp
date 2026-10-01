#include "Matrix.hpp"
#include <sstream>
#include <stdexcept>
//Конструкторы

template <typename T>
Matrix<T>::Matrix() : rows_count(0), cols_count(0) {}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : rows_count(rows), cols_count(cols), data(rows, std::vector<T>(cols)) {}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T& value)
    : rows_count(rows), cols_count(cols), data(rows, std::vector<T>(cols, value)) {}

//Копирование и присваивание

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_count(other.rows_count), cols_count(other.cols_count), data(other.data) {}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this != &other) {
        this->rows_count = other.rows_count;
        this->cols_count = other.cols_count;
        this->data = other.data;
    }
    return *this;
}

template <typename T>
Matrix<T>::~Matrix() {}
template <typename T>
std::vector<T>& Matrix<T>::operator[](size_t row) {
    // .at() проверяет границы и выбрасывает std::out_of_range при ошибке
    return data.at(row); 
}

template <typename T>
const std::vector<T>& Matrix<T>::operator[](size_t row) const {
    // Аналогичная проверка для константной версии
    return data.at(row);
}

template <typename T>
size_t Matrix<T>::rows() const { return rows_count; }

template <typename T>
size_t Matrix<T>::cols() const { return cols_count; }

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
void Matrix<T>::fillZero() { fill(T{}); }

template <typename T>
void Matrix<T>::resize(size_t rows, size_t cols) {
    rows_count = rows;
    cols_count = cols;
    data.resize(rows, std::vector<T>(cols));
}

//ВВОД / ВЫВОД

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
template class Matrix<int>;
template class Matrix<double>;
