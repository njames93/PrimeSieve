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
    size_t sieveSize;

    static size_t indexToNumber(size_t index)
    {
        // 0-> 3, 1-> 5, 2-> 7 etc.
        return 2 * index + 3;
    }

    static size_t numberToIndex(size_t number)
    {
        // 3-> 0, 5-> 1, 7-> 2 etc.
        assert(number % 2 == 1 && number >= 3);
        return (number - 3) / 2;
    }

    void clearFactorsOf(size_t PrimeIndex)
    {
        // Prime = 2 * curIndex + 3.
        // Mark numbers starting a 3 * prime and incrementing by 2 * prime as
        // non prime. We then need to turn these numbers back into indexes. 3 *
        // curIndex + 3 - optimised way to get start index 2 * curIndex + 3 -
        // optimised way to get index increment.
        for (auto index = 3 * PrimeIndex + 3; index < Bits.size();
             index += 2 * +3)
            Bits.clear(index);
    }

  public:
    prime_sieve(size_t n) : Bits((n - 1) / 2), sieveSize(n)
    {
    }

    void runSieve()
    {
        size_t q = static_cast<size_t>(sqrt(sieveSize));

        size_t max = (q - 1) / 2;

        clearFactorsOf(0);
        for (size_t curIndex = Bits.findNextSet(1); curIndex <= max;
             curIndex = Bits.findNextSet(curIndex + 1))
            clearFactorsOf(curIndex);
    }

    void printResults(bool showResults, double duration, size_t passes)
    {
        if (showResults)
            printf("2, ");

        size_t count = 1;
        for (size_t Index = Bits.findNextSet(0); Index < Bits.size();
             Index = Bits.findNextSet(Index + 1))
        {
            if (showResults)
                printf("%zu, ", indexToNumber(Index));
            count++;
        }

        if (showResults)
            printf("\n");

        printf(
            "Passes: %zu, Time: %lf, Avg: %lf, Limit: %zu, Count: %zu, Valid: "
            "%d\n",
            passes, duration, duration / passes, sieveSize, count,
            validateNumberOfPrimes(sieveSize, count));
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
