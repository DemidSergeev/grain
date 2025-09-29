#include "auth_registers.h"


using namespace grain;


void AuthRegisters::init(uint8_t accum_init[32], uint8_t shift_reg_init[32])
{
    for (int i = 0; i < 32; ++i)
    {
        accumulator |= accum_init[i];
        accumulator <<= 1;
    }

    for (int i = 0; i < 32; ++i)
    {
        shift_register |= shift_reg_init[i];
        shift_register <<= 1;
    }
}


void AuthRegisters::update(uint8_t keystream_byte, uint8_t message_byte)
{
    shift_register = (shift_register << 1) | (keystream_byte & 1);
    uint32_t message_mask = message_byte == 0 ? 0 : 0xFFFFFFFF;
    accumulator ^= message_mask & shift_register;
}