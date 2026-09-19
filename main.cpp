#include <iostream>
#include <locale>
#include "Matrix.hpp"
#include "RandomGenerator.hpp"
#include "IStreamGenerator.hpp"
#include "ConstantGenerator.hpp"
#include "Task1.hpp"
#include "Task2.hpp"

enum FillMethod
{
    RANDOM = 1,
    MANUAL = 2,
    ZEROES = 3,
    CONSTANT = 4
};

FillMethod getFillMethod()
{
    std::cout << "\nКак заполнить матрицу?" << std::endl;
    std::cout << "1 - Случайными числами" << std::endl;
    std::cout << "2 - С клавиатуры" << std::endl;
    std::cout << "3 - Нулями" << std::endl;
    std::cout << "4 - Константой" << std::endl;

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case RANDOM:   return RANDOM;
        case MANUAL:   return MANUAL;
        case ZEROES:   return ZEROES;
        case CONSTANT: return CONSTANT;
        default:
            std::cout << "Неверный выбор! По умолчанию: случайные числа." << std::endl;
            return RANDOM;
    }
}

Generator* createGenerator(FillMethod method)
{
    switch (method) {
        case RANDOM:
            return new RandomGenerator(-50, 50);
        case MANUAL:
            return new IStreamGenerator(std::cin);
        case ZEROES:
            return new ConstantGenerator(0);
        case CONSTANT: {
            int val = 0;
            std::cout << "Введите константу для заполнения: ";
            std::cin >> val;
            return new ConstantGenerator(val);
        }
        default:
            return new RandomGenerator(-50, 50);
    }
}

void fillMatrix(Matrix<int>& matrix, Generator& gen)
{
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            matrix[i][j] = gen.generate();
}

void inputDimensions(size_t& rows, size_t& cols)
{
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;
}

void executeTask1(const Matrix<int>& matrix)
{
    RandomGenerator dummy(0, 0);
    Task1 task1(matrix, &dummy);
    task1.solve();
    std::cout << "\nРезультат Task 1 (элементы, кратные 3, заменены на 0):" << std::endl;
    std::cout << task1.getMatrix();
}

void executeTask2(const Matrix<int>& matrix)
{
    RandomGenerator dummy(0, 0);
    Task2 task2(matrix, &dummy);
    task2.solve();
    std::cout << "\nРезультат Task 2 (удалены строки, где 2-й > предпоследнего):" << std::endl;
    std::cout << task2.getMatrix();
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    size_t rows = 0, cols = 0;
    inputDimensions(rows, cols);

    Matrix<int> matrix(rows, cols);

    FillMethod method = getFillMethod();
    Generator* gen = createGenerator(method);
    fillMatrix(matrix, *gen);

    std::cout << "\nИсходная матрица:" << std::endl;
    std::cout << matrix;

    executeTask1(matrix);
    executeTask2(matrix);

    delete gen;
    return 0;
}
