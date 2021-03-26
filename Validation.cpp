// -----------------------------------------------------------------------------
// validation.cpp : Lookup table to validate prime sieve count.
// -----------------------------------------------------------------------------

#include "validation.h"
#include <map>

static const std::map<unsigned, unsigned> PrimeLookup = {
    {10,
     4}, // Historical data for validating our results - the number of primes
    {100, 25}, // to be found under some limit, such as 168 primes under 1000
    {1000, 168},
    {10000, 1229},
    {100000, 9592},
    {1000000, 78498},
    {10000000, 664579},
    {100000000, 5761455},
    {1000000000, 50847534},
    {2147483647, 105097565}};

bool validateNumberOfPrimes(unsigned Limit, unsigned Expected)
{
    auto It = PrimeLookup.find(Limit);
    if (It == PrimeLookup.end())
        return false;
    return It->second == Expected;
}
