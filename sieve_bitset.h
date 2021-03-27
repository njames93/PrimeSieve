#ifndef SIEVE_BITSET_H
#define SIEVE_BITSET_H

#include <bit>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <span>

class sieve_bitset
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

  public:
    sieve_bitset(unsigned NumBits)
        : NumBits(NumBits),
          NumBitWords((NumBits + BITWORD_SIZE - 1) / BITWORD_SIZE),
          RawBits(static_cast<BitWord *>(malloc(NumBitWords * sizeof(BitWord))))
    {
        std::memset(RawBits, 0xFF, (NumBitWords - 1) * sizeof(BitWord));
        RawBits[NumBitWords - 1] = ~(~BitWord(0) << (NumBits % BITWORD_SIZE));
    }

    ~sieve_bitset()
    {
        free(RawBits);
    }
    void clear(unsigned Index)
    {
        RawBits[Index / BITWORD_SIZE] &=
            ~(BitWord(1) << (Index % BITWORD_SIZE));
    }

    bool isSet(unsigned Index) const
    {
        return (RawBits[Index / BITWORD_SIZE] &
                (BitWord(1) << (Index % BITWORD_SIZE))) != 0;
    }

    unsigned size() const
    {
        return NumBits;
    }

    unsigned count() const
    {
        unsigned Sum{0};
        for (auto Item : std::span(RawBits, NumBitWords))
        {
            Sum += std::popcount(Item);
        }
        return Sum;
    }

    unsigned findNextSet(unsigned StartIndex) const
    {
        if (StartIndex == NumBits)
            return -1;

        unsigned FirstWord = StartIndex / BITWORD_SIZE;

        // Mask out bits of the the current word that are before StartIndex
        BitWord Current = RawBits[FirstWord] & ~BitWord(0) << StartIndex;
        if (Current != 0)
            return FirstWord * BITWORD_SIZE + std::countr_zero(Current);

        for (unsigned I = FirstWord + 1; I < NumBitWords; ++I)
        {
            if (RawBits[I] != 0)
                return I * BITWORD_SIZE + std::countr_zero(RawBits[I]);
        }
        return -1;
    }
};

#endif // SIEVE_BITSET_H