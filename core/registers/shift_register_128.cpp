#include "shift_register_128.h"


using namespace grain;


ShiftRegister128::ShiftRegister128(Register128& init_state) : state(init_state) {}


uint8_t ShiftRegister128::operator[](const size_t index) const
{
    size_t word_index = index / 32;
    size_t bit_index = 31 - index % 32; // Big-endian
    /*
    Example:
    index % 32 = 15
    bit_index = 31 - 15 = 16
                          1          2          3
    index      01234567 89012345 67890123 45678901
    word     = 01110001.01010101.01010100.10001111
                               ^
    shifted  = 00000000.00000000.01110001.01010101 
                                                 ^
    */
    return (state[word_index] >> bit_index) & 1;
}


void ShiftRegister128::set_bit(const size_t index, uint8_t value)
{
    size_t word_index = index / 32;
    size_t bit_index = 31 - index % 32; // Big-endian
    uint32_t mask = 1U << bit_index;
    if (value)
        state[word_index] |= mask;
    else
        state[word_index] &= ~mask;
    /*
    Example:
    value = 0
    index % 32 = 15
    bit_index = 31 - 15 = 16
                          1          2          3
    index      01234567 89012345 67890123 45678901
    mask     = 00000000.00000001.00000000.00000000
    word     = 01110001.01010101.01010100.10001111
                               ^
    masked   = 01110001.01010100.01010100.10001111
                                                 ^
    */
}


void ShiftRegister128::shift_left_by_one(uint8_t new_bit)
{
    new_bit &= 1; // ensure it is either 0 or 1
    for (int i = 0; i < 3; ++i)
    {
        state[i] = (state[i] << i) | (state[i + 1] >> 31);
    }
    state[3] = (state[3] << 1) | new_bit;
}