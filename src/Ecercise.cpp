#include "Exercise.hpp"

Exercise::Exercise(const Matrix<int>& matrix, Generator* generator)
    : matrix(matrix), generator(generator)
{
}

Exercise::~Exercise()
{
}

Matrix<int> Exercise::getMatrix() const
{
    return matrix;
}
