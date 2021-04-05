// -----------------------------------------------------------------------------
// FFSThrees.cpp : Prime sieve ignoring multiples of 2 and 3.
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

    /// Convers an index in the bitset to its corresponding number.
    /// Theses are from a sequence of all positive numbers greater than 3 that
    /// aren't divisible by 2 or 3.
    /// 0 -> 5
    /// 1 -> 7
    /// 2 -> 11...
    static size_t indexToNumber(size_t Index)
    {
        return Index * 2 + 5 + (Index & ~1);
    }
    /// Convers an index in the bitset to its corresponding number.
    /// 5 -> 0
    /// 7 -> 1
    /// 11 -> 2...
    /// \pre \p Isn't divisible by 2 or 3 and is greater than 3.
    static size_t numberToIndex(size_t Number)
    {
        auto A = Number - 5;
        return A / 3 + (A % 3) / 2;
    }

    /// Calculates how many bits are needed for a sieve up to \p Limit.
    static size_t primeSieveSize(size_t Limit)
    {
        auto A = Limit - 5;
        auto Div = A / 6;
        auto Mod = A % 6;
        return Div * 2 + ((Mod < 2) ? 1 : 2);
    }

    /// Turns \p PrimeIndex into its prime number, then clears out every
    /// multiple of it from the bitset to mark those corresponding numbers as
    /// non prime.
    void clearMultiplesOfIndex(size_t PrimeIndex)
    {
        auto Prime = indexToNumber(PrimeIndex);
        auto StartIndex = numberToIndex(Prime * 5);
        auto Diff1 = StartIndex - PrimeIndex;
        auto Diff2 = numberToIndex(Prime * 7) - StartIndex;
        bool OddIter = true;
        for (auto Index = StartIndex; Index < Bits.size();
             Index += (OddIter ^= true) ? Diff1 : Diff2)
            Bits.clear(Index);
    }

  public:
    prime_sieve(size_t N) : Bits(primeSieveSize(N)), SieveSize(N)
    {
    }

    void runSieve()
    {
        size_t Q = static_cast<size_t>(sqrt(SieveSize));
        if (Q < 5)
            return;

        // Max is the largest index in the bit array that corresponds to a
        // number less than or equal to Q.
        size_t Max = primeSieveSize(Q);

        // 0 corresponds to the prime number 5 here.
        clearMultiplesOfIndex(0);
        // Loop over all set bits clearing all its multiples from the bitset.
        // This marks all those multiples as non prime.
        for (size_t CurIndex = Bits.findNextSet(1); CurIndex <= Max;
             CurIndex = Bits.findNextSet(CurIndex + 1))
            clearMultiplesOfIndex(CurIndex);
    }

    const sieve_bitset &getBits() const
    {
        return Bits;
    }

    void printResults(bool ShowResults, double Duration, size_t Passes)
    {
        if (ShowResults)
            printf("2, ");

        size_t Count = 2;
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
        // Add 2 as '2' and '3' are prime but not in bitset.
        return 2 + Bits.count();
    }
};

int main()
{
    benchmark<prime_sieve>();
}
