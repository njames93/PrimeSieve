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
    unsigned sieveSize;

    static unsigned indexToNumber(unsigned Index)
    {
        return Index * 2 + 5 + (Index & ~1);
    }

    static unsigned numberToIndex(unsigned Number)
    {
        auto A = Number - 5;
        return A / 3 + (A % 3) / 2;
    }

    static unsigned primeSieveSize(unsigned Limit)
    {
        auto A = Limit - 5;
        auto Div = A / 6;
        auto Mod = A % 6;
        return Div * 2 + ((Mod < 2) ? 1 : 2);
    }

    void clearFactorsOf(unsigned PrimeIndex)
    {
        auto Prime = indexToNumber(PrimeIndex);
        auto StartIndex = numberToIndex(Prime * 5);
        auto Diff1 = StartIndex - PrimeIndex;
        auto Diff2 = numberToIndex(Prime * 7) - StartIndex;
        bool OddIter = true;
        for (auto index = StartIndex; index < Bits.size();
             index += (OddIter ^= true) ? Diff1 : Diff2)
            Bits.clear(index);
    }

  public:
    prime_sieve(unsigned n) : Bits(primeSieveSize(n)), sieveSize(n)
    {
    }

    void runSieve()
    {
        unsigned q = static_cast<unsigned>(sqrt(sieveSize));

        unsigned max = (q - 1) / 2;

        clearFactorsOf(0);
        for (unsigned curIndex = Bits.findNextSet(1); curIndex <= max;
             curIndex = Bits.findNextSet(curIndex + 1))
            clearFactorsOf(curIndex);
    }

    void printResults(bool showResults, double duration, unsigned passes)
    {
        if (showResults)
            printf("2, ");

        unsigned count = 2;
        for (unsigned Index = Bits.findNextSet(0); Index < Bits.size();
             Index = Bits.findNextSet(Index + 1))
        {
            if (showResults)
                printf("%d, ", indexToNumber(Index));
            count++;
        }

        if (showResults)
            printf("\n");

        printf("Passes: %u, Time: %lf, Avg: %lf, Limit: %u, Count: %u, Valid: "
               "%d\n",
               passes, duration, duration / passes, sieveSize, count,
               validateNumberOfPrimes(sieveSize, count));
    }

    unsigned countPrimes()
    {
        // Add 2 as '2' and '3' are prime but not in bitset.
        return 2 + Bits.count();
    }
};

int main()
{
    benchmark<prime_sieve>();
}
