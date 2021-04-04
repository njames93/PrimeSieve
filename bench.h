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
    std::optional<PrimeSieve> sieve;
    for (auto SieveSize : Checks)
    {
        unsigned passes = 0;

        auto tStart = std::chrono::steady_clock::now();
        auto tEnd = tStart + BenchTime;
        while (std::chrono::steady_clock::now() < tEnd)
        {
            sieve.emplace(SieveSize);
            sieve->runSieve();
            passes++;
        }
        auto tD = std::chrono::steady_clock::now() - tStart;

        if (sieve)
        {
            sieve->printResults(
                false,
                std::chrono::duration_cast<std::chrono::duration<double>>(tD)
                    .count(),
                passes);
        }
    }
}

template <typename PrimeSieve>
void passLimitedBenchmark(std::chrono::milliseconds BenchTime,
                          unsigned PassLimit)
{
    std::optional<PrimeSieve> sieve;
    for (auto SieveSize : Checks)
    {
        unsigned passes = 0;

        auto tStart = std::chrono::steady_clock::now();
        auto tEnd = tStart + BenchTime;
        while (std::chrono::steady_clock::now() < tEnd && passes < PassLimit)
        {
            sieve.emplace(SieveSize);
            sieve->runSieve();
            passes++;
        }
        auto tD = std::chrono::steady_clock::now() - tStart;

        if (sieve)
        {
            sieve->printResults(
                false,
                std::chrono::duration_cast<std::chrono::duration<double>>(tD)
                    .count(),
                passes);
        }
    }
}

template <typename PrimeSieve> void benchmark()
{
    passLimitedBenchmark<PrimeSieve>(DefaultBenchTime, 100'000'000);
}

#endif // BENCH_H
