/**
 * @file main.cpp
 * @brief Программа работы с матрицами: ввод, заполнение, решение задач.
 */

#include <iostream>
#include <locale>
#include <string>
#include "Matrix.hpp"
#include "RandomGenerator.hpp"
#include "IStreamGenerator.hpp"
#include "ConstantGenerator.hpp"
#include "Task1.hpp"
#include "Task2.hpp"

// --- Константы конфигурации и интерфейса ---
constexpr int MIN_RAND = -50;       ///< Минимум для случайной генерации
constexpr int MAX_RAND = 50;        ///< Максимум для случайной генерации

const std::string MSG_MENU      = "\nКак заполнить матрицу?";
const std::string MSG_OPT_RAND  = "1 - Случайными числами";
const std::string MSG_OPT_MAN   = "2 - С клавиатуры";
const std::string MSG_OPT_ZERO  = "3 - Нулями";
const std::string MSG_OPT_CONST = "4 - Константой";
const std::string MSG_ERR_CHOICE= "Неверный выбор! По умолчанию: случайные числа.";
const std::string MSG_INPUT_CONST = "Введите константу: ";
const std::string MSG_INPUT_ROWS  = "Количество строк: ";
const std::string MSG_INPUT_COLS  = "Количество столбцов: ";

/// Способы заполнения матрицы
enum FillMethod { RANDOM = 1, MANUAL = 2, ZEROES = 3, CONSTANT = 4 };

/**
 * @brief Выводит меню и возвращает выбранный способ заполнения.
 * @return FillMethod Выбранный метод (по умолчанию RANDOM).
 */
FillMethod getFillMethod() {
    std::cout << MSG_MENU << std::endl
              << MSG_OPT_RAND << std::endl
              << MSG_OPT_MAN << std::endl
              << MSG_OPT_ZERO << std::endl
              << MSG_OPT_CONST << std::endl;

    int choice = 0;
    std::cin >> choice;

    switch (choice) {
        case RANDOM:   return RANDOM;
        case MANUAL:   return MANUAL;
        case ZEROES:   return ZEROES;
        case CONSTANT: return CONSTANT;
        default:
            std::cout << MSG_ERR_CHOICE << std::endl;
            return RANDOM;
    }
}

/**
 * @brief Запрашивает корректные размеры матрицы у пользователя.
 * @param[out] rows Количество строк (> 0).
 * @param[out] cols Количество столбцов (> 0).
 */
void inputDimensions(size_t& rows, size_t& cols) {
    do { std::cout << MSG_INPUT_ROWS; std::cin >> rows; } while (!rows);
    do { std::cout << MSG_INPUT_COLS; std::cin >> cols; } while (!cols);
}

/**
 * @brief Фабрика генераторов значений для матрицы.
 * @param method Способ заполнения.
 * @return Generator* Указатель на созданный генератор.
 */
Generator* createGenerator(FillMethod method) {
    switch (method) {
        case RANDOM:   return new RandomGenerator(MIN_RAND, MAX_RAND);
        case MANUAL:   return new IStreamGenerator(std::cin);
        case ZEROES:   return new ConstantGenerator(0);
        case CONSTANT: {
            int val = 0;
            std::cout << MSG_INPUT_CONST;
            std::cin >> val;
            return new ConstantGenerator(val);
        }
        default:       return new RandomGenerator(MIN_RAND, MAX_RAND);
    }
}

/**
 * @brief Заполняет матрицу значениями из генератора.
 * @param matrix Матрица для заполнения.
 * @param gen Генератор значений.
 */
void fillMatrix(Matrix<int>& matrix, Generator& gen) {
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            matrix[i][j] = gen.generate();
}

/**
 * @brief Решает и выводит результат Задания 1.
 * @param matrix Исходная матрица.
 */
void executeTask1(const Matrix<int>& matrix) {
    RandomGenerator dummy(0, 0);
    Task1 task(matrix, &dummy);
    task.solve();
    std::cout << "\n--- Task 1 (кратные 3 -> 0) ---\n" << task.getMatrix();
}

/**
 * @brief Решает и выводит результат Задания 2.
 * @param matrix Исходная матрица.
 */
void executeTask2(const Matrix<int>& matrix) {
    RandomGenerator dummy(0, 0);
    Task2 task(matrix, &dummy);
    task.solve();
    std::cout << "\n--- Task 2 (удаление строк) ---\n" << task.getMatrix();
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");


    size_t rows = 0, cols = 0;
    inputDimensions(rows, cols);
    Matrix<int> matrix(rows, cols);

    FillMethod method = getFillMethod();
    Generator* gen = createGenerator(method);
    fillMatrix(matrix, *gen);
    delete gen;

    std::cout << "\n=== Исходная матрица ===\n" << matrix;

    executeTask1(matrix);
    executeTask2(matrix);

    return 0;
}
