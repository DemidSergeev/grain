#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include <cstdint>
#include <cstddef>

#include "register_128.h"

namespace grain
{

/// @brief 128-bit shift register.
/// Is a base class for LFSR (Linear Function SR) and NFSR (Non-linear function SR)
class ShiftRegister128
{
    public:
        ShiftRegister128(const Register128& init_state);

        /// @brief Get value of bit at `index`
        /// @param index 
        /// @return Value of bit at `index`
        uint8_t operator[](const size_t) const;

        /// @brief Set bit at `index` to `value`
        /// @param index position of bit in register
        /// @param value value to which the bit would be set
        void set_bit(const size_t index, uint8_t value);

        /// @brief Shift the register's state to the left and insert the `new_bit`.
        /// @param new_bit bit to be inserted.
        void shift_left_by_one(uint8_t new_bit);

    protected:
        Register128 state;
};

} // namespace grain

#endif //SHIFT_REGISTER_H