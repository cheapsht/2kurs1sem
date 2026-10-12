#include "Exercise.hpp"

Exercise::Exercise(Matrix<int>& matrix, const Generator& generator)
    : matrix(matrix), generator(generator) {}
Matrix<int> Exercise::getMatrix() const
{
    return matrix;
}
