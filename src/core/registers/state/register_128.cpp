#include "register_128.h"


using namespace grain;


Register128::Register128(const uint32_t init_state[4])
{
    for (int i = 0; i < 4; ++i)
    {
        words[i] = init_state[i];
    }
}

Register128::Register128(const Register128& other)
{
    for (int i = 0; i < 4; ++i)
    {
        words[i] = other.words[i];
    }
}

uint32_t& Register128::operator[](const size_t index)
{
    return words[index];
}

const uint32_t& Register128::operator[](const size_t index) const
{
    return words[index];
}