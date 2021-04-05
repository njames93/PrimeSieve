// -----------------------------------------------------------------------------
// Bench.h : Provides a method to benchmark prime sieves across across the
//           range 10 to 1,000,000,000.
// -----------------------------------------------------------------------------

#ifndef BENCH_H
#define BENCH_H

#include <chrono>
#include <cstdint>
#include <optional>

constexpr std::chrono::milliseconds DefaultBenchTime(5000);

constexpr unsigned Checks[] = {
    10,         100,         1'000,         10'000,        100'000,   1'000'000,
    10'000'000, 100'000'000, 1'000'000'000, 2'147'483'647, UINT32_MAX};

template <typename PrimeSieve>
void benchmarkByTime(std::chrono::milliseconds BenchTime)
{
    std::optional<PrimeSieve> Sieve;
    for (auto SieveSize : Checks)
    {
        unsigned Passes = 0;

        auto TStart = std::chrono::steady_clock::now();
        auto TEnd = TStart + BenchTime;
        while (std::chrono::steady_clock::now() < TEnd)
        {
            Sieve.emplace(SieveSize);
            Sieve->runSieve();
            Passes++;
        }
        auto TD = std::chrono::steady_clock::now() - TStart;

        if (Sieve)
        {
            Sieve->printResults(
                false,
                std::chrono::duration_cast<std::chrono::duration<double>>(TD)
                    .count(),
                Passes);
        }
    }
}

template <typename PrimeSieve>
void passLimitedBenchmark(std::chrono::milliseconds BenchTime,
                          unsigned PassLimit)
{
    std::optional<PrimeSieve> Sieve;
    for (auto SieveSize : Checks)
    {
        unsigned Passes = 0;

        auto TStart = std::chrono::steady_clock::now();
        auto TEnd = TStart + BenchTime;
        while (std::chrono::steady_clock::now() < TEnd && Passes < PassLimit)
        {
            Sieve.emplace(SieveSize);
            Sieve->runSieve();
            Passes++;
        }
        auto TD = std::chrono::steady_clock::now() - TStart;

        if (Sieve)
        {
            Sieve->printResults(
                false,
                std::chrono::duration_cast<std::chrono::duration<double>>(TD)
                    .count(),
                Passes);
        }
    }
}

template <typename PrimeSieve> void benchmark()
{
    passLimitedBenchmark<PrimeSieve>(DefaultBenchTime, 100'000'000);
}

#endif // BENCH_H
