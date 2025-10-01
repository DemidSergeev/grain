#include "cipher.h"

using namespace grain;


Cipher::Cipher(const Key& key, const InitVector& iv) : nfsr{key}, lfsr{iv}
{
    warmup();
    init_auth_registers(); 
}


void Cipher::init_auth_registers()
{
    auto init_data = [this](uint8_t* data)
    {
        for (int i = 0; i < 32; ++i)
        {
            data[i] = keystream_iter();
        }
    };

    uint8_t accum_init[32];
    uint8_t shift_reg_init[32];

    init_data(accum_init);
    init_data(shift_reg_init);

    ar.init(accum_init, shift_reg_init);
}


void Cipher::warmup(int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        keystream_iter(true);
    }
}


uint8_t Cipher::keystream_iter(bool warmup)
{
    uint8_t pf = preoutput_function();
    uint8_t lfsr_new_bit = lfsr.generate_next_bit();
    uint8_t nfsr_new_bit = nfsr.generate_next_bit(lfsr_new_bit);

    lfsr.shift_left_by_one(lfsr_new_bit ^ (warmup ? pf : 0));
    nfsr.shift_left_by_one(nfsr_new_bit ^ (warmup ? pf : 0));

    return pf;
}


uint8_t Cipher::preoutput_function()
{
    Nfsr128& b = nfsr;
    Lfsr128& s = lfsr;

    auto h = [b, s]()
    {
        return (b[12] & s[8]) ^ (s[13] & s[20]) ^ (b[95] & s[42]) ^
                (s[60] & s[79]) ^ (b[12] & b[95] & s[94]);
    };

    return h() ^ s[93] ^ b[2] ^ b[15] ^ b[36] ^ b[45] ^ b[64] ^ b[73] ^ b[89];
}


void Cipher::encrypt(uint8_t* data, size_t length, uint8_t* output) {
    for (size_t i = 0; i < length; ++i) {
        uint8_t keystream_byte = 0;
        for (int j = 0; j < 16; ++j) {
            if (j % 2 == 0) {
                keystream_byte |= keystream_iter();
                keystream_byte <<= 1;
            } else {
            // Update authentication registers with every odd keystream bit
                ar.update(keystream_iter(), data[i]);
            }
        }
        output[i] = data[i] ^ keystream_byte;
    }
}


void Cipher::decrypt(uint8_t* data, size_t length, uint8_t* output) {
    // Decryption is the same as encryption in Grain-128a
    encrypt(data, length, output);
}