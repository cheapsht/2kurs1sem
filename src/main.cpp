/**
 * @file main.cpp
 * @brief Основная программа для работы с матрицами и решения задач.
 */
#include <stdexcept>
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
 * @brief Запросить ненулевую размерность.
 * @param message Указатель на строку приглашения к вводу.
 * @return Введённая размерность.
 * @throws std::invalid_argument Если message равен nullptr.
 */
size_t inputDimension(const char* message);
/**
 * @brief Решает и выводит результат Задания 1.
 * @param matrix Исходная матрица.
 */
void executeTask1(const Matrix<int>& matrix);
/**
 * @brief Решает и выводит результат Задания 2.
 * @param matrix Исходная матрица.
 */
void executeTask2(const Matrix<int>& matrix);

/**
 * @brief main - точка входа
 */
int main() {
    constexpr int MIN_RAND = -50;   ///< Минимум для случайной генерации
    constexpr int MAX_RAND = 50;    ///< Максимум для случайной генерации

    // 1. Инициализация матрицы
    size_t rows = inputDimension(MSG_INPUT_ROWS);
    size_t cols = inputDimension(MSG_INPUT_COLS);
    Matrix<int> matrix(rows, cols);

    // 2. Выбор метода и создание генератора
    // 2. Выбор метода и заполнение матрицы
FillMethod method = getFillMethod();

switch (method) {
    case RANDOM: {
        RandomGenerator gen(MIN_RAND, MAX_RAND);
        matrix.fill(gen);
        break;
    }

    case MANUAL: {
        IStreamGenerator gen(std::cin);
        matrix.fill(gen);
        break;
    }

    case ZEROES: {
        ConstantGenerator gen(0);
        matrix.fill(gen);
        break;
    }

    case CONSTANT: {
        int val = 0;
        std::cout << MSG_INPUT_CONST;
        std::cin >> val;

        ConstantGenerator gen(val);
        matrix.fill(gen);
        break;
    }

    default: {
        RandomGenerator gen(MIN_RAND, MAX_RAND);
        matrix.fill(gen);
        break;
    }
}

    // 4. Вывод исходных данных
    std::cout << "\n=== Исходная матрица ===\n" << matrix;

    // 5. Решение задач
    executeTask1(matrix);
    executeTask2(matrix);

    return 0;
}
size_t inputDimension(const char* message)
{
    if (message == nullptr) {
        throw std::invalid_argument(
            "Сообщение не должно быть nullptr"
        );
    }

    size_t value = 0;

    do {
        std::cout << message;
        std::cin >> value;
    } while (!value);

    return value;
}
void executeTask1(const Matrix<int>& matrix) {
    Task1 task(matrix);
    task.solve();
    std::cout << "\n--- Task 1 (кратные 3 -> 0) ---\n" << task.getMatrix();
}
void executeTask2(const Matrix<int>& matrix) {
    Task2 task(matrix);
    task.solve();
    std::cout << "\n--- Task 2 (удаление строк) ---\n" << task.getMatrix();
}
