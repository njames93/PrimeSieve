Implementation and benchmarks of Dave Plumbers prime sieve using find first set.

https://github.com/davepl/Primes

https://www.youtube.com/watch?v=D3h62rgewZM

# Results

Basic system info:
```
CPU:       Ryzen 2600X 
Memory:    32GB Dual channel 4 * 8GB DIMMS.
OS:        Ubuntu 20.04.1
Compiler:  clang-11
```

## 03

### Daves
```
Passes: 1000000, Time: 0.045906, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 1000000, Time: 0.064095, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 1000000, Time: 0.515878, Avg: 0.000001, Limit: 1000, Count: 168, Valid: 1
Passes: 1000000, Time: 5.391447, Avg: 0.000005, Limit: 10000, Count: 1229, Valid: 1
Passes: 251546, Time: 15.000065, Avg: 0.000060, Limit: 100000, Count: 9592, Valid: 1
Passes: 22342, Time: 15.000048, Avg: 0.000671, Limit: 1000000, Count: 78498, Valid: 1
Passes: 2004, Time: 15.004117, Avg: 0.007487, Limit: 10000000, Count: 664579, Valid: 1
Passes: 146, Time: 15.047212, Avg: 0.103063, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 5, Time: 17.516977, Avg: 3.503395, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 2, Time: 15.517033, Avg: 7.758517, Limit: 2147483647, Count: 105097565, Valid: 1
```

### AdvBitManip
```
Passes: 1000000, Time: 0.048081, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 1000000, Time: 0.108871, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 1000000, Time: 0.486957, Avg: 0.000000, Limit: 1000, Count: 168, Valid: 1
Passes: 1000000, Time: 4.913975, Avg: 0.000005, Limit: 10000, Count: 1229, Valid: 1
Passes: 301555, Time: 15.000046, Avg: 0.000050, Limit: 100000, Count: 9592, Valid: 1
Passes: 27168, Time: 15.000485, Avg: 0.000552, Limit: 1000000, Count: 78498, Valid: 1
Passes: 2454, Time: 15.002429, Avg: 0.006113, Limit: 10000000, Count: 664579, Valid: 1
Passes: 173, Time: 15.019167, Avg: 0.086816, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 5, Time: 15.113925, Avg: 3.022785, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 3, Time: 20.894022, Avg: 6.964674, Limit: 2147483647, Count: 105097565, Valid: 1
```

## 03 -march=native

### Daves
```
Passes: 1000000, Time: 0.040294, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 1000000, Time: 0.065508, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 1000000, Time: 0.423662, Avg: 0.000000, Limit: 1000, Count: 168, Valid: 1
Passes: 1000000, Time: 4.312212, Avg: 0.000004, Limit: 10000, Count: 1229, Valid: 1
Passes: 325615, Time: 15.000045, Avg: 0.000046, Limit: 100000, Count: 9592, Valid: 1
Passes: 28459, Time: 15.000490, Avg: 0.000527, Limit: 1000000, Count: 78498, Valid: 1
Passes: 2524, Time: 15.001941, Avg: 0.005944, Limit: 10000000, Count: 664579, Valid: 1
Passes: 165, Time: 15.003354, Avg: 0.090929, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 5, Time: 15.753089, Avg: 3.150618, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 3, Time: 21.857813, Avg: 7.285938, Limit: 2147483647, Count: 105097565, Valid: 1
```

### AdvBitManip
```
Passes: 1000000, Time: 0.045085, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 1000000, Time: 0.103998, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 1000000, Time: 0.487193, Avg: 0.000000, Limit: 1000, Count: 168, Valid: 1
Passes: 1000000, Time: 4.759544, Avg: 0.000005, Limit: 10000, Count: 1229, Valid: 1
Passes: 311104, Time: 15.000001, Avg: 0.000048, Limit: 100000, Count: 9592, Valid: 1
Passes: 28113, Time: 15.000061, Avg: 0.000534, Limit: 1000000, Count: 78498, Valid: 1
Passes: 2499, Time: 15.000378, Avg: 0.006003, Limit: 10000000, Count: 664579, Valid: 1
Passes: 182, Time: 15.076992, Avg: 0.082841, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 6, Time: 17.867965, Avg: 2.977994, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 3, Time: 20.416346, Avg: 6.805449, Limit: 2147483647, Count: 105097565, Valid: 1
```

For some reason the original code seemed to benefit quite heavily from tuned assembly.
The AdvBitManip didn't appear to benefit quite as heavily from the same option.
Its also interesting to note that the original code performed better at smaller sample sizes, however as the size grew the tables began to turn. This is likely because as you get to larger numbers, the distances between consecutive primes grows. The AdvBitManip code takes advantage here as it can quickly skip across the larger gaps.

