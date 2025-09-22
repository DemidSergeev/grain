#ifndef REGISTER128_H
#define REGISTER128_H

#include <cstdint>
#include <cstddef>

namespace grain {
    /// @brief 128-bit register
    class Register128 {
    public:
        Register128(const uint32_t init_state[4]);
        Register128(Register128&);

        uint32_t& operator[](const size_t);
        const uint32_t& operator[](const size_t) const;
    private:
        uint32_t words[4];

    };
}

#endif // REGISTER128_H