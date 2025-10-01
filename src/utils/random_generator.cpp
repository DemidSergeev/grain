#include "random_generator.h"


using namespace grain::random;


uint32_t RandomGenerator::operator()()
{
    return 0xDEADBEEF;
}