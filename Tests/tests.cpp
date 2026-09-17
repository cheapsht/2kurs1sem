#include <cassert>
#include <sstream>
#include "Matrix.hpp"
#include "RandomGenerator.hpp"
#include "IStreamGenerator.hpp"
#include "Task1.hpp"
#include "Task2.hpp"

//
// Тесты для класса Matrix
//

void test_matrix_default_ctor()
{
    // Проверка создания пустой матрицы
    Matrix<int> m;
    assert(m.rows() == 0);
    assert(m.cols() == 0);
}

void test_matrix_param_ctor()
{
    // Проверка создания матрицы заданного размера
    Matrix<int> m(3, 4);
    assert(m.rows() == 3);
    assert(m.cols() == 4);
}

void test_matrix_fill()
{
    // Проверка заполнения матрицы константным значением
    Matrix<int> m(2, 2, 5);
    assert(m[0][0] == 5);
    assert(m[1][1] == 5);
    
    // Проверка метода fill
    m.fill(10);
    assert(m[0][1] == 10);
}

void test_matrix_copy_and_assign()
{
    // Проверка корректности глубокого копирования
    Matrix<int> m1(2, 2, 7);
    Matrix<int> m2 = m1; // конструктор копирования
    
    m2[0][0] = 99; // изменяем копию
    
    // Оригинал не должен измениться
    assert(m1[0][0] == 7);
    assert(m2[0][0] == 99);
    
    // Проверка оператора присваивания
    Matrix<int> m3(1, 1, 0);
    m3 = m1;
    assert(m3.rows() == 2);
    assert(m3[1][1] == 7);
}

void test_matrix_io()
{
    // Проверка строкового представления и операторов потока
    Matrix<int> m(2, 2, 3);
    std::string str = m.toString();
    assert(!str.empty());
    
    std::stringstream ss;
    ss << m;
    assert(ss.str() == str);
}

//
// Тесты для генераторов
//

void test_random_generator()
{
    // Проверка попадания значений в заданный диапазон
    RandomGenerator gen(-10, 10);
    for (int i = 0; i < 100; ++i) {
        int val = gen.generate();
        assert(val >= -10 && val <= 10);
    }
}

void test_istream_generator()
{
    // Имитация ввода с клавиатуры через строковый поток
    std::istringstream input("42 15 -7");
    IStreamGenerator gen(input);
    
    assert(gen.generate() == 42);
    assert(gen.generate() == 15);
    assert(gen.generate() == -7);
}

//
// Тесты для Task 1 (Вариант 12)
// Замена элемента, кратного 3, на 0
//

void test_task1_basic()
{
    // Обычный случай: есть кратные и не кратные 3
    Matrix<int> m(2, 3);
    m[0][0] = 3;  // кратно 3
    m[0][1] = 4;  // не кратно
    m[0][2] = 6;  // кратно 3
    m[1][0] = 7;  // не кратно
    m[1][1] = 9;  // кратно 3
    m[1][2] = 2;  // не кратно

    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();

    Matrix<int> res = task.getMatrix();
    assert(res[0][0] == 0);
    assert(res[0][1] == 4);
    assert(res[0][2] == 0);
    assert(res[1][0] == 7);
    assert(res[1][1] == 0);
    assert(res[1][2] == 2);
}

void test_task1_negative()
{
    // Проверка с отрицательными числами (в C++ -3 % 3 == 0)
    Matrix<int> m(1, 2);
    m[0][0] = -3;
    m[0][1] = -4;

    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();

    Matrix<int> res = task.getMatrix();
    assert(res[0][0] == 0);
    assert(res[0][1] == -4);
}

// 
// Тесты для Task 2 (Вариант 12)
// Удалить строки, где 2-й элемент > предпоследнего
//

void test_task2_delete_some()
{
    // Матрица 3x4. Должна остаться только средняя строка
    Matrix<int> m(3, 4);
    m[0][0] = 1; m[0][1] = 5; m[0][2] = 3; m[0][3] = 2; // 5 > 3 (удалить)
    m[1][0] = 1; m[1][1] = 2; m[1][2] = 5; m[1][3] = 2; // 2 <= 5 (оставить)
    m[2][0] = 1; m[2][1] = 8; m[2][2] = 1; m[2][3] = 2; // 8 > 1 (удалить)

    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();

    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 1);
    assert(res.cols() == 4);
    assert(res[0][1] == 2); // проверяем элемент оставшейся строки
}

void test_task2_delete_none()
{
    // Ни одна строка не удовлетворяет условию удаления
    Matrix<int> m(2, 4);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 5; m[0][3] = 3; // 2 <= 5
    m[1][0] = 1; m[1][1] = 1; m[1][2] = 3; m[1][3] = 2; // 1 <= 3

    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();

    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 2); // размер не изменился
}

void test_task2_delete_all()
{
    // Все строки должны быть удалены
    Matrix<int> m(2, 4);
    m[0][0] = 1; m[0][1] = 10; m[0][2] = 3; m[0][3] = 2; // 10 > 3
    m[1][0] = 1; m[1][1] = 8;  m[1][2] = 1; m[1][3] = 2; // 8 > 1

    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();

    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 0);
}

void test_task2_small_cols()
{
    // Матрица с 1 столбцом. Удаление невозможно по условию, должно пройти без ошибок
    Matrix<int> m(2, 1);
    m[0][0] = 5;
    m[1][0] = 5;

    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve(); // просто проверяем, что не упало с выходом за границы массива

    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 2);
    assert(res.cols() == 1);
}

//
// Запуск всех тестов
//

void run_all_tests()
{
    test_matrix_default_ctor();
    test_matrix_param_ctor();
    test_matrix_fill();
    test_matrix_copy_and_assign();
    test_matrix_io();
    
    test_random_generator();
    test_istream_generator();
    
    test_task1_basic();
    test_task1_negative();
    
    test_task2_delete_some();
    test_task2_delete_none();
    test_task2_delete_all();
    test_task2_small_cols();
}

int main()
{
    run_all_tests();
    
    return 0;
}
