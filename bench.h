// -----------------------------------------------------------------------------
// Bench.h : Provides a method to benchmark prime sieves across across the
//           range 10 to 1,000,000,000.
// -----------------------------------------------------------------------------

#ifndef BENCH_H
#define BENCH_H

#include <chrono>
#include <optional>

template <typename PrimeSieve>
void benchmark(std::chrono::milliseconds BenchTime)
{
    unsigned Checks[] = {
        10,        100,        1'000,       10'000,        100'000,
        1'000'000, 10'000'000, 100'000'000, 1'000'000'000, 2'147'483'647};
    for (auto SieveSize : Checks)
    {
        unsigned passes = 0;
        std::optional<PrimeSieve> sieve;

        auto tStart = std::chrono::steady_clock::now();
        auto tEnd = tStart + BenchTime;
        while (std::chrono::steady_clock::now() < tEnd && passes < 1'000'000)
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

#endif // BENCH_H
