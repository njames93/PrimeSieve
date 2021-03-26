// -----------------------------------------------------------------------------
// validation.h : Lookup table to validate prime sieve count.
// -----------------------------------------------------------------------------

#ifndef VALIDATION_H
#define VALIDATION_H

/// Performs a lookup of number of primes up to and including \p Limit and
/// returns true if the returned value is equal to \p Expected. Note: Lookup
/// table only contains entries for 10, 100, 100... 1,000,000,000. Any value not
/// inclusive will return false.
bool validateNumberOfPrimes(unsigned Limit, unsigned Expected);

#endif // VALIDATION_H
