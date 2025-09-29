#include "nfsr_128.h"


using namespace grain;


Nfsr128::Nfsr128(const Key& key) : ShiftRegister128(make_state(key)) {}


uint8_t Nfsr128::generate_next_bit(uint8_t lfsr_bit)
{
    lfsr_bit &= 1;

    Register128& s = state; // for brevity
    uint8_t new_bit = lfsr_bit ^ s[0] ^ s[26] ^ s[56] ^ s[91] ^ s[96] ^
        (s[3] & s[67]) ^ (s[11] & s[13]) ^ (s[17] & s[18]) ^
        (s[27] & s[59]) ^ (s[40] & s[48]) ^ (s[61] & s[65]) ^
        (s[68] & s[84]) ^ (s[88] & s[92] & s[93] & s[95]) ^
        (s[22] & s[24] & s[25]) ^ (s[70] & s[78] & s[82]);

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