#ifndef NFSR_H
#define NFSR_H

#include "shift_register_128.h"
#include "init_state.h"

namespace grain
{

class Nfsr128 : public ShiftRegister128
{
    public:
        Nfsr128(const Key& key);
        uint8_t generate_next_bit(uint8_t lfsr_bit);

    private:
        static const Register128 make_state(const Key& key);
};

} // namespace grain
#endif // NFSR_H