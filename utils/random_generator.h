#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H


#include <cstdint>


namespace grain
{

namespace random
{

class RandomGenerator
{
    public:
        uint32_t operator()();
};

} // namespace random

} // namespace grain

#endif // RANDOM_GENERATOR_H