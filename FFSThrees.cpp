// -----------------------------------------------------------------------------
// FFSThrees.cpp : Prime sieve ignoring multiples of 2 and 3.
// -----------------------------------------------------------------------------

#include "bench.h"
#include "validation.h"
#include <bit>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
    unsigned sieveSize;

    void clearBit(unsigned Index)
    {
        RawBits[Index / BITWORD_SIZE] &=
            ~(BitWord(1) << (Index % BITWORD_SIZE));
    }

    bool isSet(unsigned Index) const
    {
        return (RawBits[Index / BITWORD_SIZE] &
                (BitWord(1) << (Index % BITWORD_SIZE))) != 0;
    }

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

        // Check subsequent words.
        // The code below is based on search for the first _set_ bit. If
        // we're searching for the first _unset_, we just take the
        // complement of each word before we use it and apply
        // the same method.

        // Mask out bits of the the current word that are before StartIndex
        BitWord Current = RawBits[FirstWord] & ~BitWord(0) << StartIndex;
        if (Current != 0)
            return FirstWord * BITWORD_SIZE + std::countr_zero(Current);

        for (unsigned i = FirstWord + 1; i < NumBitWords; ++i)
        {
            if (RawBits[i] != 0)
                return i * BITWORD_SIZE + std::countr_zero(RawBits[i]);
        }
        return -1;
    }

    void clearFactorsOf(unsigned PrimeIndex)
    {
        auto Prime = indexToNumber(PrimeIndex);
        auto StartIndex = numberToIndex(Prime * 5);
        auto Diff1 = StartIndex - PrimeIndex;
        auto Diff2 = numberToIndex(Prime * 7) - StartIndex;
        bool OddIter = true;
        for (auto index = StartIndex; index < NumBits;
             index += (OddIter ^= true) ? Diff1 : Diff2)
            clearBit(index);
    }

  public:
    prime_sieve(int n)
        : NumBits(primeSieveSize(n)),
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
        unsigned q = static_cast<unsigned>(sqrt(sieveSize));

        unsigned max = (q - 1) / 2;

        clearFactorsOf(0);
        for (unsigned curIndex = findNextSetBit(1); curIndex <= max;
             curIndex = findNextSetBit(curIndex + 1))
            clearFactorsOf(curIndex);
    }

    void printResults(bool showResults, double duration, int passes)
    {
        if (showResults)
            printf("2, ");

        int count = 2;
        for (unsigned Index = findNextSetBit(0); Index < NumBits;
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
        return 2 + countSetBits();
    }
};

int main()
{
    benchmark<prime_sieve>();
}
