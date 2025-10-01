#include "nfsr_128.h"


using namespace grain;


Nfsr128::Nfsr128(const Key& key) : ShiftRegister128(make_state(key)) {}


uint8_t Nfsr128::generate_next_bit(uint8_t lfsr_bit)
{
    lfsr_bit &= 1;

    Nfsr128& r = *this; // for brevity
    uint8_t new_bit = lfsr_bit ^ r[0] ^ r[26] ^ r[56] ^ r[91] ^ r[96] ^
        (r[3] & r[67]) ^ (r[11] & r[13]) ^ (r[17] & r[18]) ^
        (r[27] & r[59]) ^ (r[40] & r[48]) ^ (r[61] & r[65]) ^
        (r[68] & r[84]) ^ (r[88] & r[92] & r[93] & r[95]) ^
        (r[22] & r[24] & r[25]) ^ (r[70] & r[78] & r[82]);

    return new_bit;
}


const Register128 Nfsr128::make_state(const Key& key)
{
    uint32_t state[4];

    for (int i = 0; i < 4; ++i)
    {
        state[i] = key.words[i];
    }

    return Register128{state};
}