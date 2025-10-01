#ifndef INIT_STATE_H
#define INIT_STATE_H


#include "random_generator.h"
#include <cstdint>

namespace grain
{

/// @brief Initial vector for LFSR
struct InitVector
{
    uint32_t words[3];
};

/// @brief Key for NFSR
struct Key
{
    uint32_t words[4];
};


namespace random
{

/// @brief Generate random Initialization Vector for LFSR
/// @return 96-bit Initialization Vector
InitVector init_vector();

/// @brief Generate random Key for NFSR
/// @return 128-bit Key
Key key();

} // namespace random

} // namespace grain

#endif // INIT_STATE_H