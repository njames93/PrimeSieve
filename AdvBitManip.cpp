// -----------------------------------------------------------------------------
// AdvBitManip.cpp : Prime sieve using advanced bit intrinsics.
// -----------------------------------------------------------------------------

#include "bench.h"
#include "validation.h"
#include <bit>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <span>

class prime_sieve
{
  private:
    typedef uintptr_t BitWord;

    enum
    {
        BITWORD_SIZE = (unsigned)sizeof(BitWord) * CHAR_BIT
    };
    unsigned NumBits;
    unsigned NumBitWords;
    BitWord *RawBits;
    int sieveSize;

    void clearBit(unsigned Index)
    {
        RawBits[Index / BITWORD_SIZE] &=
            ~(BitWord(1) << (Index % BITWORD_SIZE));
    }

    bool isSet(unsigned Index) const
    {
        return (RawBits[Index / BITWORD_SIZE] &
                (1 << (Index % BITWORD_SIZE))) != 0;
    }

    static unsigned indexToNumber(unsigned index)
    {
        // 0-> 3, 1-> 5, 2-> 7 etc.
        return 2 * index + 3;
    }

    static unsigned numberToIndex(unsigned number)
    {
        // 3-> 0, 5-> 1, 7-> 2 etc.
        assert(number % 2 == 1 && number >= 3);
        return (number - 3) / 2;
    }

    unsigned countSetBits()
    {
        unsigned Sum{0};
        for (auto Item : std::span(RawBits, NumBitWords))
        {
            Sum += std::popcount(Item);
        }
        return Sum;
    }
    unsigned findNextSetBit(unsigned StartIndex)
    {
        if (StartIndex == NumBits)
            return -1;

        unsigned FirstWord = StartIndex / BITWORD_SIZE;
        unsigned LastWord = NumBitWords - 1;

        // Check subsequent words.
        // The code below is based on search for the first _set_ bit. If
        // we're searching for the first _unset_, we just take the
        // complement of each word before we use it and apply
        // the same method.
        for (unsigned i = FirstWord; i <= LastWord; ++i)
        {
            BitWord Copy = RawBits[i];

            if (i == FirstWord && (StartIndex % BITWORD_SIZE) != 0)
            {
                unsigned FirstBit = StartIndex % BITWORD_SIZE;
                Copy &= ~(~BitWord(0) >> (BITWORD_SIZE - FirstBit));
            }
            if (Copy != 0)
                return i * BITWORD_SIZE + std::countr_zero(Copy);
        }
        return -1;
    }

    void clearFactorsOf(unsigned PrimeIndex)
    {
        // Prime = 2 * curIndex + 3.
        // Mark numbers starting a 3 * prime and incrementing by 2 * prime as
        // non prime. We then need to turn these numbers back into indexes. 3 *
        // curIndex + 3 - optimised way to get start index 2 * curIndex + 3 -
        // optimised way to get index increment.
        for (auto index = 3 * PrimeIndex + 3; index < NumBits;
             index += 2 * PrimeIndex + 3)
            clearBit(index);
    }

  public:
    prime_sieve(int n)
        : NumBits((n - 1) / 2),
          NumBitWords((NumBits + BITWORD_SIZE - 1) / BITWORD_SIZE),
          RawBits(
              static_cast<BitWord *>(malloc(NumBitWords * sizeof(BitWord)))),
          sieveSize(n)
    {
        std::memset(RawBits, 0xFF, (NumBitWords - 1) * sizeof(BitWord));
        RawBits[NumBitWords - 1] = ~(~BitWord(0) << (NumBits % BITWORD_SIZE));
    }

    ~prime_sieve()
    {
        free(RawBits);
    }

    void runSieve()
    {
        int q = sqrt(sieveSize);

        int max = (q - 1) / 2;

        clearFactorsOf(0);
        for (unsigned curIndex = findNextSetBit(1); curIndex <= max;
             curIndex = findNextSetBit(curIndex + 1))
            clearFactorsOf(curIndex);
    }

    void printResults(bool showResults, double duration, int passes)
    {
        if (showResults)
            printf("2, ");

        int count = 1;
        for (unsigned Index = findNextSetBit(0); Index <= NumBits;
             Index = findNextSetBit(Index + 1))
        {
            auto Prime = indexToNumber(Index);
            if (showResults)
                printf("%d, ", Prime);
            count++;
        }

        if (showResults)
            printf("\n");

        printf("Passes: %d, Time: %lf, Avg: %lf, Limit: %d, Count: %d, Valid: "
               "%d\n",
               passes, duration, duration / passes, sieveSize, count,
               validateNumberOfPrimes(sieveSize, count));
    }

    int countPrimes()
    {
        // Add 1 as '2' is prime but not in bitset.
        return 1 + countSetBits();
    }
};

int main()
{
    using namespace std::chrono_literals;
    benchmark<prime_sieve>(15000ms);
}
