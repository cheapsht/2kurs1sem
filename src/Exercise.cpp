#include "Exercise.hpp"

Exercise::Exercise(const Matrix<int>& matrix)
    : matrix(matrix) {}
Matrix<int> Exercise::getMatrix() const
{
    return matrix;
}
