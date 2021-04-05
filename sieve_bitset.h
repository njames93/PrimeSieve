#ifndef SIEVE_BITSET_H
#define SIEVE_BITSET_H

#include <bit>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <span>

// FIXME: These should be in their own implementation file
#if __has_cpp_attribute(likely)
#define BRANCH_LIKELY [[likely]]
#else
#define BRANCH_LIKELY
#endif

#if __has_cpp_attribute(unlikely)
#define BRANCH_UNLIKELY [[unlikely]]
#else
#define BRANCH_UNLIKELY
#endif

class sieve_bitset
{
  private:
    typedef uintptr_t BitWord;
    static constexpr size_t BITWORD_SIZE = sizeof(BitWord) * CHAR_BIT;
    size_t NumBits;
    size_t NumBitWords;
    BitWord *RawBits;

  public:
    static constexpr size_t npos = ~size_t(0);

    sieve_bitset(size_t NumBits)
        : NumBits(NumBits),
          NumBitWords((NumBits + BITWORD_SIZE - 1) / BITWORD_SIZE),
          RawBits(static_cast<BitWord *>(malloc(NumBitWords * sizeof(BitWord))))
    {
        // Set all the bits to true as right now we expect all values are prime.
        std::fill(RawBits, RawBits + NumBitWords - 1, ~BitWord(0));
        // Ensure any high bits in the final word are zeroed out. This saves
        // unnecessary work in operations that look for set bits getting
        // confused by bits above NumBits.
        RawBits[NumBitWords - 1] = ~(~BitWord(0) << (NumBits % BITWORD_SIZE));
    }

    ~sieve_bitset()
    {
        free(RawBits);
    }

    /// Clears the given bit at \p Index.
    void clear(size_t Index)
    {
        RawBits[Index / BITWORD_SIZE] &=
            ~(BitWord(1) << (Index % BITWORD_SIZE));
    }

    /// Returns if the given bit at \p Index is in a set state.
    bool isSet(size_t Index) const
    {
        return (RawBits[Index / BITWORD_SIZE] &
                (BitWord(1) << (Index % BITWORD_SIZE))) != 0;
    }

    /// Returns the total number of bits regardless of whether they are in a set
    /// or cleared state.
    size_t size() const
    {
        return NumBits;
    }

    /// Returns the total number of bits set.
    size_t count() const
    {
        size_t Sum{0};
        for (auto Item : std::span(RawBits, NumBitWords))
        {
            Sum += std::popcount(Item);
        }
        return Sum;
    }

    /// Returns the index of the next set bit inclusive of \p StartIndex,
    /// returns npos if StartIndex is out of range, or there are no more bits
    /// set.
    size_t findNextSet(size_t StartIndex) const
    {
        // clang-format off
        // see https://llvm.org/PR49840.
        if (StartIndex >= NumBits) BRANCH_UNLIKELY
            return npos;

        size_t FirstWord = StartIndex / BITWORD_SIZE;

        // If the current Word contains set bits above StartIndex, do a trailing
        // zero count on the remaining bits in the word.
        if (BitWord Current = RawBits[FirstWord] >> (StartIndex % BITWORD_SIZE))
            BRANCH_LIKELY
            return StartIndex + std::countr_zero(Current);

        // Otherwise loop through the remaining words in the bitset finding the
        // first one that set.
        for (size_t I = FirstWord + 1; I != NumBitWords; ++I)
        {
            // If == 0 there are no bits set so we can skip to next iter.
            if (RawBits[I]) BRANCH_LIKELY
                return I * BITWORD_SIZE + std::countr_zero(RawBits[I]);
        }
        // No more set, return npos to indicate.
        return npos;
        // clang-format on
    }
};

#endif // SIEVE_BITSET_H