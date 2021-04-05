// -----------------------------------------------------------------------------
// FFSTwos.cpp : Prime sieve using Find First Set.
// -----------------------------------------------------------------------------

#include "bench.h"
#include "sieve_bitset.h"
#include "validation.h"
#include <cassert>
#include <cmath>
#include <cstdio>
class prime_sieve
{
  private:
    sieve_bitset Bits;
    size_t SieveSize;

    /// Convers an \p Index in the bitset to its corresponding number.
    /// Theses are from a sequence of all odd numbers greater than 2.
    /// 0 -> 3
    /// 1 -> 5
    /// 2 -> 7...
    static size_t indexToNumber(size_t Index)
    {
        return 2 * Index + 3;
    }

    /// Convers an index in the bitset to its corresponding \p Number.
    /// 3 -> 0
    /// 5 -> 1
    /// 7 -> 2...
    /// \pre \p Is an odd number > 2.
    static size_t numberToIndex(size_t Number)
    {
        assert(Number % 2 == 1 && Number >= 3);
        return (Number - 3) / 2;
    }

    /// Calculates how many bits are needed for a sieve up to \p Limit.
    static size_t primeSieveSize(size_t Limit)
    {
        return (Limit - 1) / 2;
    }

    /// Turns \p PrimeIndex into its prime number, then clears out every
    /// multiple of it from the bitset to mark those corresponding numbers as
    /// non prime.
    void clearMultiplesOfIndex(size_t PrimeIndex)
    {
        // Prime = 2 * curIndex + 3.
        // Mark numbers starting a 3 * prime and incrementing by 2 * prime as
        // non prime. We then need to turn these numbers back into indexes. 3 *
        // curIndex + 3 - optimised way to get start index 2 * curIndex + 3 -
        // optimised way to get index increment.
        for (auto Index = 3 * PrimeIndex + 3; Index < Bits.size();
             Index += 2 * PrimeIndex + 3)
            Bits.clear(Index);
    }

  public:
    prime_sieve(size_t N) : Bits(primeSieveSize(N)), SieveSize(N)
    {
    }

    void runSieve()
    {
        size_t Q = static_cast<size_t>(sqrt(SieveSize));

        // Max is the largest index in the bit array that corresponds to a
        // number less than or equal to Q.
        size_t Max = primeSieveSize(Q);

        // 0 corresponds to the prime number 3 here.
        clearMultiplesOfIndex(0);
        // Loop over all set bits clearing all its multiples from the bitset.
        // This marks all those multiples as non prime.
        for (size_t CurIndex = Bits.findNextSet(1); CurIndex <= Max;
             CurIndex = Bits.findNextSet(CurIndex + 1))
            clearMultiplesOfIndex(CurIndex);
    }

    void printResults(bool ShowResults, double Duration, size_t Passes)
    {
        if (ShowResults)
            printf("2, ");

        size_t Count = 1;
        for (size_t Index = Bits.findNextSet(0); Index < Bits.size();
             Index = Bits.findNextSet(Index + 1))
        {
            if (ShowResults)
                printf("%zu, ", indexToNumber(Index));
            Count++;
        }

        if (ShowResults)
            printf("\n");

        printf(
            "Passes: %zu, Time: %lf, Avg: %lf, Limit: %zu, Count: %zu, Valid: "
            "%d\n",
            Passes, Duration, Duration / Passes, SieveSize, Count,
            validateNumberOfPrimes(SieveSize, Count));
    }

    size_t countPrimes()
    {
        // Add 1 as '2' is prime but not in bitset.
        return 1 + Bits.count();
    }
};

int main()
{
    benchmark<prime_sieve>();
}
