#include "ConstantGenerator.hpp"

ConstantGenerator::ConstantGenerator(int value) : constantValue(value) {}

int ConstantGenerator::generate()
{
    return constantValue;
}
