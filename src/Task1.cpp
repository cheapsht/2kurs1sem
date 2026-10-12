#include "Task1.hpp"

Task1::Task1(Matrix<int>& matrix, const Generator& generator)
    : Exercise(matrix, generator) {}

void Task1::solve()
{
    for (size_t j = 0; j < matrix.cols(); ++j) {
        for (size_t i = 0; i < matrix.rows(); ++i) {
            if (matrix[i][j] % 3 == 0) {
                matrix[i][j] = 0;
            }
        }
    }
}
