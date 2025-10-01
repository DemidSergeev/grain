#include <cstdint>


namespace grain
{

class AuthRegisters
{
    public:
        void init(uint8_t accum_init[32], uint8_t shift_reg_init[32]);
        void update(uint8_t keystream_byte, uint8_t message_byte);

    private:
        uint32_t shift_register {};
        uint32_t accumulator {};
};

} // namespace grain