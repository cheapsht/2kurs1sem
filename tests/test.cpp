#include <gtest/gtest.h>
#include <sstream>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"
#include "Task1.h"
#include "Task2.h"

//тесты матрицы

TEST(MatrixTest, DefaultConstructor) {
    Matrix<int> m;
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
}

TEST(MatrixTest, ParamConstructor) {
    Matrix<int> m(3, 4);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 4);
}

TEST(MatrixTest, FillConstructor) {
    Matrix<int> m(2, 3, 7);
    ASSERT_EQ(m[0][0], 7);
    ASSERT_EQ(m[1][2], 7);
}

TEST(MatrixTest, CopyConstructor) {
    Matrix<int> m1(2, 2, 5);
    Matrix<int> m2(m1);
    ASSERT_EQ(m2[0][0], 5);
    ASSERT_EQ(m2[1][1], 5);
}

TEST(MatrixTest, AssignmentOperator) {
    Matrix<int> m1(2, 2, 10);
    Matrix<int> m2(1, 1, 0);
    m2 = m1;
    ASSERT_EQ(m2.rows(), 2);
    ASSERT_EQ(m2[0][0], 10);
}

TEST(MatrixTest, IndexOperator) {
    Matrix<int> m(3, 3);
    m[0][0] = 100;
    m[2][2] = 200;
    ASSERT_EQ(m[0][0], 100);
    ASSERT_EQ(m[2][2], 200);
}

TEST(MatrixTest, RowsColsGetters) {
    Matrix<int> m(5, 7);
    ASSERT_EQ(m.rows(), 5);
    ASSERT_EQ(m.cols(), 7);
}

TEST(MatrixTest, ToStringNotEmpty) {
    Matrix<int> m(2, 2, 3);
    std::string str = m.toString();
    ASSERT_FALSE(str.empty());
    ASSERT_NE(str.find("3"), std::string::npos);
}

TEST(MatrixTest, FillMethod) {
    Matrix<int> m(3, 3);
    m.fill(42);
    ASSERT_EQ(m[0][0], 42);
    ASSERT_EQ(m[2][2], 42);
}

TEST(MatrixTest, FillZeroMethod) {
    Matrix<int> m(2, 2, 100);
    m.fillZero();
    ASSERT_EQ(m[0][0], 0);
    ASSERT_EQ(m[1][1], 0);
}

TEST(MatrixTest, ResizeMethod) {
    Matrix<int> m(2, 2);
    m.resize(4, 5);
    ASSERT_EQ(m.rows(), 4);
    ASSERT_EQ(m.cols(), 5);
}

TEST(MatrixTest, OutputStream) {
    Matrix<int> m(2, 2, 5);
    std::stringstream ss;
    ss << m;
    ASSERT_FALSE(ss.str().empty());
}

TEST(MatrixTest, InputStream) {
    Matrix<int> m(2, 2);
    std::istringstream input("1 2 3 4");
    input >> m;
    ASSERT_EQ(m[0][0], 1);
    ASSERT_EQ(m[0][1], 2);
    ASSERT_EQ(m[1][0], 3);
    ASSERT_EQ(m[1][1], 4);
}

TEST(MatrixTest, SelfAssignment) {
    Matrix<int> m(2, 2, 5);
    m = m;
    ASSERT_EQ(m[0][0], 5);
    ASSERT_EQ(m.rows(), 2);
}
// ТЕСТЫ ГЕНЕРАТОРОВ
TEST(RandomGeneratorTest, RangeCheck) {
    RandomGenerator gen(-10, 10);
    for (int i = 0; i < 100; ++i) {
        int val = gen.generate();
        ASSERT_GE(val, -10); // Greater or Equal
        ASSERT_LE(val, 10);  // Less or Equal
    }
}

TEST(RandomGeneratorTest, PositiveRange) {
    RandomGenerator gen(1, 100);
    for (int i = 0; i < 50; ++i) {
        int val = gen.generate();
        ASSERT_GE(val, 1);
        ASSERT_LE(val, 100);
    }
}

TEST(IStreamGeneratorTest, BasicRead) {
    std::istringstream input("42 15 -7");
    IStreamGenerator gen(input);
    ASSERT_EQ(gen.generate(), 42);
    ASSERT_EQ(gen.generate(), 15);
    ASSERT_EQ(gen.generate(), -7);
}

TEST(IStreamGeneratorTest, EmptyStream) {
    std::istringstream input("");
    IStreamGenerator gen(input);
    ASSERT_EQ(gen.generate(), 0);
}

TEST(ConstantGeneratorTest, ZeroValue) {
    ConstantGenerator gen(0);
    ASSERT_EQ(gen.generate(), 0);
    ASSERT_EQ(gen.generate(), 0);
}

TEST(ConstantGeneratorTest, SpecificValue) {
    ConstantGenerator gen(42);
    ASSERT_EQ(gen.generate(), 42);
}

TEST(ConstantGeneratorTest, NegativeValue) {
    ConstantGenerator gen(-10);
    ASSERT_EQ(gen.generate(), -10);
}

//тесты заданий

TEST(Task1Test, BasicMultiplesOfThree) {
    Matrix<int> m(2, 3);
    m[0][0] = 3;  m[0][1] = 4;  m[0][2] = 6;
    m[1][0] = 7;  m[1][1] = 9;  m[1][2] = 2;
    
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res[0][0], 0); // 3 -> 0
    ASSERT_EQ(res[0][1], 4); // 4 unchanged
    ASSERT_EQ(res[0][2], 0); // 6 -> 0
    ASSERT_EQ(res[1][0], 7); // 7 unchanged
    ASSERT_EQ(res[1][1], 0); // 9 -> 0
    ASSERT_EQ(res[1][2], 2); // 2 unchanged
}

TEST(Task1Test, AllMultiples) {
    Matrix<int> m(2, 2);
    m[0][0] = 3;  m[0][1] = 6;
    m[1][0] = 9;  m[1][1] = 12;
    
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res[0][0], 0);
    ASSERT_EQ(res[0][1], 0);
    ASSERT_EQ(res[1][0], 0);
    ASSERT_EQ(res[1][1], 0);
}

TEST(Task1Test, NoMultiples) {
    Matrix<int> m(2, 2);
    m[0][0] = 1;  m[0][1] = 2;
    m[1][0] = 4;  m[1][1] = 5;
    
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res[0][0], 1);
    ASSERT_EQ(res[0][1], 2);
    ASSERT_EQ(res[1][0], 4);
    ASSERT_EQ(res[1][1], 5);
}

TEST(Task1Test, NegativeNumbers) {
    Matrix<int> m(1, 2);
    m[0][0] = -3; 
    m[0][1] = -4;
    
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res[0][0], 0);   // -3 кратно 3
    ASSERT_EQ(res[0][1], -4);  // -4 не кратно
}

TEST(Task1Test, ZeroElement) {
    Matrix<int> m(1, 2);
    m[0][0] = 0;  
    m[0][1] = 5;
    
    RandomGenerator dummy(0, 0);
    Task1 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res[0][0], 0); // 0 кратен любому числу, остается 0
    ASSERT_EQ(res[0][1], 5);
}

TEST(Task2Test, DeleteSomeRows) {
    Matrix<int> m(3, 4);
    m[0][0] = 1; m[0][1] = 5; m[0][2] = 3; m[0][3] = 2; // 5 > 2? YES -> delete
    m[1][0] = 1; m[1][1] = 2; m[1][2] = 5; m[1][3] = 2; // 2 > 5? NO  -> keep
    m[2][0] = 1; m[2][1] = 8; m[2][2] = 1; m[2][3] = 2; // 8 > 2? YES -> delete
    
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res.rows(), 1);
    ASSERT_EQ(res.cols(), 4);
    ASSERT_EQ(res[0][1], 2);
}

TEST(Task2Test, DeleteNone) {
    Matrix<int> m(2, 4);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 5; m[0][3] = 3; // 2 > 3? NO
    m[1][0] = 1; m[1][1] = 1; m[1][2] = 3; m[1][3] = 2; // 1 > 2? NO
    
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res.rows(), 2);
}

TEST(Task2Test, DeleteAllRows) {
    Matrix<int> m(2, 4);
    m[0][0] = 1; m[0][1] = 10; m[0][2] = 3; m[0][3] = 2; // 10 > 2? YES
    m[1][0] = 1; m[1][1] = 8;  m[1][2] = 1; m[1][3] = 2; // 8 > 2? YES
    
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res.rows(), 0);
}

TEST(Task2Test, EqualElements) {
    Matrix<int> m(2, 4);
    m[0][0] = 1; m[0][1] = 5; m[0][2] = 3; m[0][3] = 2; // 5 > 2? YES
    m[1][0] = 1; m[1][1] = 3; m[1][2] = 5; m[1][3] = 3; // 3 > 3? NO (равны)
    
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res.rows(), 1);
    ASSERT_EQ(res[0][1], 3);
}

TEST(Task2Test, SmallColumns) {
    Matrix<int> m(2, 1);
    m[0][0] = 5; 
    m[1][0] = 5;
    
    RandomGenerator dummy(0, 0);
    Task2 task(m, &dummy);
    task.solve();
    
    // При 1 столбце 2-й элемент и предпоследний — это один и тот же элемент.
    // Условие "2-й > предпоследнего" никогда не выполнится.
    Matrix<int> res = task.getMatrix();
    ASSERT_EQ(res.rows(), 2);
    ASSERT_EQ(res.cols(), 1);
}
