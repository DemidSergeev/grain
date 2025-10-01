#ifndef LFSR_H
#define LFSR_H

#include "shift_register_128.h"
#include "init_state.h"

namespace grain
{

class Lfsr128 : public ShiftRegister128
{
    public:
        Lfsr128(const InitVector& iv);
        uint8_t generate_next_bit();

    private:
        static const Register128 make_state(const InitVector& iv);
};

} // namespace grain

#endif // LFSR_H