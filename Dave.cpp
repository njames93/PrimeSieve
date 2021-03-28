// -----------------------------------------------------------------------------
// PrimeCPP.cpp : Dave's Garage Prime Sieve in C++.
// -----------------------------------------------------------------------------

#include "bench.h"
#include "validation.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

class prime_sieve
{
  private:
    unsigned sieveSize = 0;
    unsigned char *rawbits = nullptr;

    bool validateResults()
    {
        return validateNumberOfPrimes(sieveSize, countPrimes());
    }

    bool GetBit(unsigned index)
    {
        assert(index % 2 != 0);
        index = index / 2;
        return ((rawbits[index / 8]) & (1 << (index % 8))) != 0;
    }

    void ClearBit(unsigned index)
    {
        assert(index % 2 != 0);
        index = index / 2;
        rawbits[index / 8] &= ~(1 << (index % 8));
    }

  public:
    prime_sieve(unsigned n)
    {
        sieveSize = n;
        rawbits = (unsigned char *)malloc(n / 8 + 1);
        if (rawbits)
            memset(rawbits, 0xff, n / 8 + 1);
    }

    ~prime_sieve()
    {
        free(rawbits);
    }

    void runSieve()
    {
        unsigned factor = 3;
        unsigned q = static_cast<unsigned>(sqrt(sieveSize));

        while (factor <= q)
        {
            for (unsigned num = factor; num < sieveSize; num += 2)
            {
                if (GetBit(num))
                {
                    factor = num;
                    break;
                }
            }
            for (unsigned num = factor * 3; num < sieveSize; num += factor * 2)
                ClearBit(num);

            factor += 2;
        }
    }

    void printResults(bool showResults, double duration, unsigned passes)
    {
        if (showResults)
            printf("2, ");

        unsigned count = 1;
        for (unsigned num = 3; num <= sieveSize; num += 2)
        {
            if (GetBit(num))
            {
                if (showResults)
                    printf("%d, ", num);
                count++;
            }
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
        unsigned count = 1;
        for (unsigned i = 3; i < sieveSize; i += 2)
            if (GetBit(i))
                count++;
        return count;
    }
};

int main()
{
    benchmark<prime_sieve>();
}
