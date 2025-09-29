#ifndef CIPHER_H
#define CIPHER_H

#include "nfsr_128.h"
#include "lfsr_128.h"
#include "auth_registers.h"

#include <cstdint>
#include <cstddef>


namespace grain
{

/// @brief Implementation of Grain-128a cipher
class Cipher {
    public:
        /// @brief Initialize cipher instance
        /// @param key initialization key for NFSR
        /// @param iv initialization vector for LFSR
        Cipher(const Key& key, const InitVector& iv);

        /// @brief Encrypt data stored under `data` pointer, write encrypted to `output`
        /// @param data pointer to data to be encrypted
        /// @param length length of data to be encrypted
        /// @param output pointer to memory to store output
        void encrypt(uint8_t *data, size_t length, uint8_t *output);
        
        /// @brief Decrypt data stored under `data` pointer, write decrypted to `output`
        /// @param data pointer to data to be decrypted
        /// @param length length of data to be decrypted
        /// @param output pointer to memory to store output
        void decrypt(uint8_t *data, size_t length, uint8_t *output);

    private:
        Nfsr128 nfsr;
        Lfsr128 lfsr;
        AuthRegisters ar;

        /// @brief Clock a number of iterations without using keystream results
        /// @param iterations number of iterations to clock
        void warmup(int iterations = 256);

        /// @brief Initialize authentication registers by first 64 keystream cycles
        void init_auth_registers();
        uint8_t keystream_iter(bool warmup = false);
        uint8_t preoutput_function();
};

} // namespace grain

#endif // CIPHER_H