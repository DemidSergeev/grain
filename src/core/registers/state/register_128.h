#ifndef REGISTER128_H
#define REGISTER128_H

#include <cstdint>
#include <cstddef>

namespace grain
{

/// @brief 128-bit register, providing access to 32-bit words by index.
class Register128
{
    public:
        Register128(const uint32_t init_state[4]);
        Register128(const Register128&);

        /// @brief Provides mutable access to the register's 32-bit words by index.
        /// @param index Index of the word (0-3).
        /// @return Reference to the 32-bit word at the specified index.
        uint32_t& operator[](const size_t);

        /// @brief Provides read-only access to the register's 32-bit words by index.
        /// @param index Index of the word (0-3).
        /// @return Const reference to the 32-bit word at the specified index.
        const uint32_t& operator[](const size_t) const;

    private:
        uint32_t words[4];
};

} // namespace grain

#endif // REGISTER128_H