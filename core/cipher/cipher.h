#ifndef CIPHER_H
#define CIPHER_H

#include "shift_registers.h"
#include <cstdint>
#include <cstddef>

namespace grain {
    class Cipher {
    public:
        void encrypt(uint8_t *data, size_t length, uint8_t *output);
        void decrypt(uint8_t *data, size_t length, uint8_t *output);

    private:
        NFSR nfsr;
        LFSR lfsr;

        void init();
        void warmup();
        uint8_t keystream_iter(bool warmup = false);
        uint8_t preoutput_function();
    };
}

#endif // CIPHER_H