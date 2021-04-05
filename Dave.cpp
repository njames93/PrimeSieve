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
    unsigned SieveSize = 0;
    unsigned char *Rawbits = nullptr;

    bool validateResults()
    {
        return validateNumberOfPrimes(SieveSize, countPrimes());
    }

    bool getBit(unsigned Index)
    {
        assert(Index % 2 != 0);
        Index = Index / 2;
        return ((Rawbits[Index / 8]) & (1 << (Index % 8))) != 0;
    }

    void clearBit(unsigned Index)
    {
        assert(Index % 2 != 0);
        Index = Index / 2;
        Rawbits[Index / 8] &= ~(1 << (Index % 8));
    }

  public:
    prime_sieve(unsigned N)
        : SieveSize(N), Rawbits((unsigned char *)malloc(N / 8 + 1))
    {

        if (Rawbits)
            memset(Rawbits, 0xff, N / 8 + 1);
    }

    ~prime_sieve()
    {
        free(Rawbits);
    }

    void runSieve()
    {
        unsigned Factor = 3;
        unsigned Q = static_cast<unsigned>(sqrt(SieveSize));

        while (Factor <= Q)
        {
            for (unsigned Num = Factor; Num < SieveSize; Num += 2)
            {
                if (getBit(Num))
                {
                    Factor = Num;
                    break;
                }
            }
            for (unsigned Num = Factor * 3; Num < SieveSize; Num += Factor * 2)
                clearBit(Num);

            Factor += 2;
        }
    }

    void printResults(bool ShowResults, double Duration, unsigned Passes)
    {
        if (ShowResults)
            printf("2, ");

        unsigned Count = 1;
        for (unsigned Num = 3; Num <= SieveSize; Num += 2)
        {
            if (getBit(Num))
            {
                if (ShowResults)
                    printf("%d, ", Num);
                Count++;
            }
        }

        if (ShowResults)
            printf("\n");

        printf("Passes: %u, Time: %lf, Avg: %lf, Limit: %u, Count: %u, Valid: "
               "%d\n",
               Passes, Duration, Duration / Passes, SieveSize, Count,
               validateNumberOfPrimes(SieveSize, Count));
    }

    unsigned countPrimes()
    {
        unsigned Count = 1;
        for (unsigned I = 3; I < SieveSize; I += 2)
            if (getBit(I))
                Count++;
        return Count;
    }
};

int main()
{
    benchmark<prime_sieve>();
}
