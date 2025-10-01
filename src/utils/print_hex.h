#ifndef PRINT_HEX_H
#define PRINT_HEX_H


#include <cstdio>
#include <cstdint>


namespace grain
{

namespace utils
{

void print_hex(const uint8_t* data, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        printf("%02X", data[i]);
        if ((i + 1) % 4 == 0)
        {
            printf(" ");
        }
    }
    printf("\n");
}

} // namespace utils

} // namespace grain

#endif // PRINT_HEX_H