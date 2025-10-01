#include "lfsr_128.h"


using namespace grain;


Lfsr128::Lfsr128(const InitVector& iv) : ShiftRegister128(make_state(iv)) {}


uint8_t Lfsr128::generate_next_bit()
{
    Lfsr128& r = *this; // for brevity;
    uint8_t new_bit = r[0] ^ r[7] ^ r[38] ^ r[70] ^ r[81] ^ r[96];

    return new_bit;
}


const Register128 Lfsr128::make_state(const InitVector& iv)
{
    uint32_t state[4];

    for (int i = 0; i < 3; ++i)
    {
        state[i] = iv.words[i];
    }
    state[3] = 0xFFFFFFFE; // Last word is 31 ones and 1 zero.

    return Register128{state};
}