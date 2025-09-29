#include "init_state.h"


using namespace grain;


random::RandomGenerator rng{};

InitVector random::init_vector()
{
    return InitVector { rng(), rng(), rng() };
}


Key random::key()
{
    return Key { rng(), rng(), rng(), rng() };
}