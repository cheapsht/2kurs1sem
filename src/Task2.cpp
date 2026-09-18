#include "Task2.hpp"

Task2::Task2(const Matrix<int>& matrix, Generator* generator)
    : Exercise(matrix, generator) {}

void Task2::solve()
{
    if (matrix.cols() < 2) return;

    Matrix<int> result;
    size_t newRows = 0;

    for (size_t i = 0; i < matrix.rows(); ++i) {
        int second = matrix[i][1];
        int prelast = matrix[i][matrix.cols() - 2];
        if (second <= prelast) {
            newRows++;
        }
    }

    result.resize(newRows, matrix.cols());

    size_t newRow = 0;
    for (size_t i = 0; i < matrix.rows(); ++i) {
        int second = matrix[i][1];
        int prelast = matrix[i][matrix.cols() - 2];

        if (second <= prelast) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                result[newRow][j] = matrix[i][j];
            }
            newRow++;
        }
    }

    matrix = result;
}
