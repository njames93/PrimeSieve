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
    size_t NumBits;
    size_t NumBitWords;
    BitWord *RawBits;

  public:
    static constexpr size_t npos = ~0ULL;

    sieve_bitset(size_t NumBits)
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
    void clear(size_t Index)
    {
        RawBits[Index / BITWORD_SIZE] &=
            ~(BitWord(1) << (Index % BITWORD_SIZE));
    }

    bool isSet(size_t Index) const
    {
        return (RawBits[Index / BITWORD_SIZE] &
                (BitWord(1) << (Index % BITWORD_SIZE))) != 0;
    }

    size_t size() const
    {
        return NumBits;
    }

    size_t count() const
    {
        size_t Sum{0};
        for (auto Item : std::span(RawBits, NumBitWords))
        {
            Sum += std::popcount(Item);
        }
        return Sum;
    }

    size_t findNextSet(size_t StartIndex) const
    {
        if (StartIndex == NumBits)
            return npos;

        size_t FirstWord = StartIndex / BITWORD_SIZE;
        size_t ExtraBits = StartIndex % BITWORD_SIZE;

        if (BitWord Current = RawBits[FirstWord] >> ExtraBits; Current != 0)
            return FirstWord * BITWORD_SIZE + std::countr_zero(Current) +
                   ExtraBits;

        for (size_t I = FirstWord + 1; I != NumBitWords; ++I)
        {
            if (RawBits[I] != 0)
                return I * BITWORD_SIZE + std::countr_zero(RawBits[I]);
        }
        return npos;
    }
};

#endif // SIEVE_BITSET_H