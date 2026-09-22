#include <cassert>
#include <sstream>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"
#include "Task1.h"
#include "Task2.h"

// Matrix
void test_matrix_default_ctor() {
    Matrix<int> m;
    assert(m.rows() == 0 && m.cols() == 0);
}

void test_matrix_param_ctor() {
    Matrix<int> m(3, 4);
    assert(m.rows() == 3 && m.cols() == 4);
}

void test_matrix_fill_ctor() {
    Matrix<int> m(2, 3, 7);
    assert(m[0][0] == 7 && m[1][2] == 7);
}

void test_matrix_copy_ctor() {
    Matrix<int> m1(2, 2, 5);
    Matrix<int> m2(m1);
    assert(m2[0][0] == 5 && m2[1][1] == 5);
}

void test_matrix_assignment() {
    Matrix<int> m1(2, 2, 10);
    Matrix<int> m2(1, 1, 0);
    m2 = m1;
    assert(m2.rows() == 2 && m2[0][0] == 10);
}

void test_matrix_index_operator() {
    Matrix<int> m(3, 3);
    m[0][0] = 100;
    m[2][2] = 200;
    assert(m[0][0] == 100 && m[2][2] == 200);
}

void test_matrix_rows_cols() {
    Matrix<int> m(5, 7);
    assert(m.rows() == 5 && m.cols() == 7);
}

void test_matrix_to_string() {
    Matrix<int> m(2, 2, 3);
    std::string str = m.toString();
    assert(!str.empty() && str.find("3") != std::string::npos);
}

void test_matrix_fill() {
    Matrix<int> m(3, 3);
    m.fill(42);
    assert(m[0][0] == 42 && m[2][2] == 42);
}

void test_matrix_fill_zero() {
    Matrix<int> m(2, 2, 100);
    m.fillZero();
    assert(m[0][0] == 0 && m[1][1] == 0);
}

void test_matrix_resize() {
    Matrix<int> m(2, 2);
    m.resize(4, 5);
    assert(m.rows() == 4 && m.cols() == 5);
}

void test_matrix_output_stream() {
    Matrix<int> m(2, 2, 5);
    std::stringstream ss;
    ss << m;
    assert(!ss.str().empty());
}

void test_matrix_input_stream() {
    Matrix<int> m(2, 2);
    std::istringstream input("1 2 3 4");
    input >> m;
    assert(m[0][0] == 1 && m[0][1] == 2 && m[1][0] == 3 && m[1][1] == 4);
}

void test_matrix_self_assignment() {
    Matrix<int> m(2, 2, 5);
    m = m;
    assert(m[0][0] == 5 && m.rows() == 2);
}

// RandomGenerator
void test_random_generator_range() {
    RandomGenerator gen(-10, 10);
    for (int i = 0; i < 100; ++i) {
        int val = gen.generate();
        assert(val >= -10 && val <= 10);
    }
}

void test_random_generator_positive_range() {
    RandomGenerator gen(1, 100);
    for (int i = 0; i < 50; ++i) {
        int val = gen.generate();
        assert(val >= 1 && val <= 100);
    }
}

// IStreamGenerator
void test_istream_generator_basic() {
    std::istringstream input("42 15 -7");
    IStreamGenerator gen(input);
    assert(gen.generate() == 42 && gen.generate() == 15 && gen.generate() == -7);
}

void test_istream_generator_empty() {
    std::istringstream input("");
    IStreamGenerator gen(input);
    assert(gen.generate() == 0);
}

// ConstantGenerator
void test_constant_generator_zero() {
    ConstantGenerator gen(0);
    assert(gen.generate() == 0 && gen.generate() == 0);
}

void test_constant_generator_value() {
    ConstantGenerator gen(42);
    assert(gen.generate() == 42 && gen.generate() == 42);
}

void test_constant_generator_negative() {
    ConstantGenerator gen(-10);
    assert(gen.generate() == -10);
}

// Task1
void test_task1_basic() {
    Matrix<int> m(2, 3);
    m[0][0] = 3;  m[0][1] = 4;  m[0][2] = 6;
    m[1][0] = 7;  m[1][1] = 9;  m[1][2] = 2;
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res[0][0] == 0 && res[0][1] == 4 && res[0][2] == 0);
    assert(res[1][0] == 7 && res[1][1] == 0 && res[1][2] == 2);
}

void test_task1_all_multiples() {
    Matrix<int> m(2, 2);
    m[0][0] = 3;  m[0][1] = 6;
    m[1][0] = 9;  m[1][1] = 12;
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res[0][0] == 0 && res[0][1] == 0 && res[1][0] == 0 && res[1][1] == 0);
}

void test_task1_no_multiples() {
    Matrix<int> m(2, 2);
    m[0][0] = 1;  m[0][1] = 2;
    m[1][0] = 4;  m[1][1] = 5;
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res[0][0] == 1 && res[0][1] == 2 && res[1][0] == 4 && res[1][1] == 5);
}

void test_task1_negative() {
    Matrix<int> m(1, 2);
    m[0][0] = -3; m[0][1] = -4;
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res[0][0] == 0 && res[0][1] == -4);
}

void test_task1_zero_element() {
    Matrix<int> m(1, 2);
    m[0][0] = 0;  m[0][1] = 5;
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res[0][0] == 0 && res[0][1] == 5);
}

// Task2
void test_task2_delete_some() {
    Matrix<int> m(3, 4);
    m[0][0] = 1; m[0][1] = 5; m[0][2] = 3; m[0][3] = 2;
    m[1][0] = 1; m[1][1] = 2; m[1][2] = 5; m[1][3] = 2;
    m[2][0] = 1; m[2][1] = 8; m[2][2] = 1; m[2][3] = 2;
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 1 && res.cols() == 4 && res[0][1] == 2);
}

void test_task2_delete_none() {
    Matrix<int> m(2, 4);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 5; m[0][3] = 3;
    m[1][0] = 1; m[1][1] = 1; m[1][2] = 3; m[1][3] = 2;
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 2);
}

void test_task2_delete_all() {
    Matrix<int> m(2, 4);
    m[0][0] = 1; m[0][1] = 10; m[0][2] = 3; m[0][3] = 2;
    m[1][0] = 1; m[1][1] = 8;  m[1][2] = 1; m[1][3] = 2;
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 0);
}

void test_task2_equal_elements() {
    Matrix<int> m(2, 4);
    m[0][0] = 1; m[0][1] = 5; m[0][2] = 3; m[0][3] = 2;
    m[1][0] = 1; m[1][1] = 3; m[1][2] = 5; m[1][3] = 3;
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 1 && res[0][1] == 3);
}

void test_task2_small_cols() {
    Matrix<int> m(2, 1);
    m[0][0] = 5; m[1][0] = 5;
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    Matrix<int> res = task.getMatrix();
    assert(res.rows() == 2 && res.cols() == 1);
}

int main()
{
    test_matrix_default_ctor();
    test_matrix_param_ctor();
    test_matrix_fill_ctor();
    test_matrix_copy_ctor();
    test_matrix_assignment();
    test_matrix_index_operator();
    test_matrix_rows_cols();
    test_matrix_to_string();
    test_matrix_fill();
    test_matrix_fill_zero();
    test_matrix_resize();
    test_matrix_output_stream();
    test_matrix_input_stream();
    test_matrix_self_assignment();

    test_random_generator_range();
    test_random_generator_positive_range();
    test_istream_generator_basic();
    test_istream_generator_empty();
    test_constant_generator_zero();
    test_constant_generator_value();
    test_constant_generator_negative();

    test_task1_basic();
    test_task1_all_multiples();
    test_task1_no_multiples();
    test_task1_negative();
    test_task1_zero_element();

    test_task2_delete_some();
    test_task2_delete_none();
    test_task2_delete_all();
    test_task2_equal_elements();
    test_task2_small_cols();

    return 0;
}
