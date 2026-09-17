#include "Task2.hpp"

Task2::Task2(const Matrix<int>& matrix, Generator* generator)
    : Exercise(matrix, generator)
{
}

void Task2::solve()
{

    if (matrix.cols() < 2) return;
    
    std::vector<size_t> rowsToKeep;
    
    for (size_t i = 0; i < matrix.rows(); ++i) {
        int second = matrix[i][1];
        int prelast = matrix[i][matrix.cols() - 2];
        
        if (second <= prelast) {
            rowsToKeep.push_back(i);
        }
    }
    
    Matrix<int> newMatrix(rowsToKeep.size(), matrix.cols());
    
    for (size_t i = 0; i < rowsToKeep.size(); ++i) {
        size_t originalRow = rowsToKeep[i];
        for (size_t j = 0; j < matrix.cols(); ++j) {
            newMatrix[i][j] = matrix[originalRow][j];
        }
    }
    

    matrix = newMatrix;
}
