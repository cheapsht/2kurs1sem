#include "IStreamGenerator.hpp"

IStreamGenerator::IStreamGenerator(std::istream& in)
    : in{in}
{
}

int IStreamGenerator::generate()
{
    int value = 0;
    this->in >> value;
    return value;
}
