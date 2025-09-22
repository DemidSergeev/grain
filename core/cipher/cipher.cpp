#include "cipher.h"

using namespace grain;

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