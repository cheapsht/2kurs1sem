/**
 * @file main.cpp
 * @brief Основная программа для работы с матрицами и решения задач.
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
#define MSG_MENU        "\nКак заполнить матрицу?"
#define MSG_OPT_RAND    "1 - Случайными числами"
#define MSG_OPT_MAN     "2 - С клавиатуры"
#define MSG_OPT_ZERO    "3 - Нулями"
#define MSG_OPT_CONST   "4 - Константой"
#define MSG_ERR_CHOICE  "Неверный выбор! По умолчанию: случайные числа."
#define MSG_INPUT_CONST "Введите константу: "
#define MSG_INPUT_ROWS  "Количество строк: "
#define MSG_INPUT_COLS  "Количество столбцов: "

/// Способы заполнения матрицы
enum FillMethod { RANDOM = 1, MANUAL = 2, ZEROES = 3, CONSTANT = 4 };
/**
 * @brief Отображает меню и возвращает выбранный способ заполнения.
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
    do { 
        std::cout << MSG_INPUT_ROWS; 
        std::cin >> rows; 
    } while (!rows);

    do { 
        std::cout << MSG_INPUT_COLS; 
        std::cin >> cols; 
    } while (!cols);
}
/**
 * @brief Заполняет матрицу, используя существующий метод Matrix::fill().
 * @note Для генераторов RANDOM/MANUAL вся матрица заполнится ПЕРВЫМ 
 *       сгенерированным значением (ограничение текущего интерфейса fill(value)).
 *       Для CONSTANT/ZEROES работает корректно.
 */
void fillMatrix(Matrix<int>& matrix, Generator& gen) {
    matrix.fill(gen.generate()); 
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

/**
 * @brief main - точка входа
 */
int main() {
    constexpr int MIN_RAND = -50;   ///< Минимум для случайной генерации
    constexpr int MAX_RAND = 50;    ///< Максимум для случайной генерации

    // 1. Инициализация матрицы
    size_t rows = 0, cols = 0;
    inputDimensions(rows, cols);
    Matrix<int> matrix(rows, cols);

    // 2. Выбор метода и создание генератора
    FillMethod method = getFillMethod();
    Generator* gen = nullptr;

    switch (method) {
        case RANDOM:   
            gen = new RandomGenerator(MIN_RAND, MAX_RAND); 
            break;
        case MANUAL:   
            gen = new IStreamGenerator(std::cin); 
            break;
        case ZEROES:   
            gen = new ConstantGenerator(0); 
            break;
        case CONSTANT: {
            int val = 0;
            std::cout << MSG_INPUT_CONST;
            std::cin >> val;
            gen = new ConstantGenerator(val);
            break;
        }
        default:       
            gen = new RandomGenerator(MIN_RAND, MAX_RAND);
    }

    // 3. Заполнение матрицы
    fillMatrix(matrix, *gen);
    delete gen;

    // 4. Вывод исходных данных
    std::cout << "\n=== Исходная матрица ===\n" << matrix;

    // 5. Решение задач
    executeTask1(matrix);
    executeTask2(matrix);

    return 0;
}
