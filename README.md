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
Passes: 100000000, Time: 3.243232, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 100000000, Time: 5.699103, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 39958581, Time: 20.000000, Avg: 0.000001, Limit: 1000, Count: 168, Valid: 1
Passes: 3778059, Time: 20.000003, Avg: 0.000005, Limit: 10000, Count: 1229, Valid: 1
Passes: 342596, Time: 20.000007, Avg: 0.000058, Limit: 100000, Count: 9592, Valid: 1
Passes: 30610, Time: 20.000606, Avg: 0.000653, Limit: 1000000, Count: 78498, Valid: 1
Passes: 2729, Time: 20.005983, Avg: 0.007331, Limit: 10000000, Count: 664579, Valid: 1
Passes: 180, Time: 20.060686, Avg: 0.111448, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 6, Time: 21.938437, Avg: 3.656406, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 3, Time: 25.899516, Avg: 8.633172, Limit: 2147483647, Count: 105097565, Valid: 1
```

### FFSTwos
```
Passes: 100000000, Time: 3.576860, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 100000000, Time: 10.210874, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 44140479, Time: 20.000000, Avg: 0.000000, Limit: 1000, Count: 168, Valid: 1
Passes: 4340745, Time: 20.000003, Avg: 0.000005, Limit: 10000, Count: 1229, Valid: 1
Passes: 394027, Time: 20.000002, Avg: 0.000051, Limit: 100000, Count: 9592, Valid: 1
Passes: 36423, Time: 20.000008, Avg: 0.000549, Limit: 1000000, Count: 78498, Valid: 1
Passes: 3186, Time: 20.002128, Avg: 0.006278, Limit: 10000000, Count: 664579, Valid: 1
Passes: 210, Time: 20.003326, Avg: 0.095254, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 7, Time: 22.407134, Avg: 3.201019, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 3, Time: 22.005517, Avg: 7.335172, Limit: 2147483647, Count: 105097565, Valid: 1
```

### FFSThrees
```
Passes: 100000000, Time: 3.512979, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 100000000, Time: 8.504156, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 58204466, Time: 20.000000, Avg: 0.000000, Limit: 1000, Count: 168, Valid: 1
Passes: 6444321, Time: 20.000001, Avg: 0.000003, Limit: 10000, Count: 1229, Valid: 1
Passes: 619084, Time: 20.000003, Avg: 0.000032, Limit: 100000, Count: 9592, Valid: 1
Passes: 55938, Time: 20.000322, Avg: 0.000358, Limit: 1000000, Count: 78498, Valid: 1
Passes: 4978, Time: 20.002046, Avg: 0.004018, Limit: 10000000, Count: 664579, Valid: 1
Passes: 404, Time: 20.001944, Avg: 0.049510, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 8, Time: 21.131088, Avg: 2.641386, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 4, Time: 24.541511, Avg: 6.135378, Limit: 2147483647, Count: 105097565, Valid: 1
```

## 03 -march=native

### Daves
```
Passes: 100000000, Time: 3.296889, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 100000000, Time: 5.097393, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 50362056, Time: 20.000000, Avg: 0.000000, Limit: 1000, Count: 168, Valid: 1
Passes: 4947494, Time: 20.000002, Avg: 0.000004, Limit: 10000, Count: 1229, Valid: 1
Passes: 446895, Time: 20.000023, Avg: 0.000045, Limit: 100000, Count: 9592, Valid: 1
Passes: 39276, Time: 20.000456, Avg: 0.000509, Limit: 1000000, Count: 78498, Valid: 1
Passes: 3441, Time: 20.000764, Avg: 0.005812, Limit: 10000000, Count: 664579, Valid: 1
Passes: 221, Time: 20.041402, Avg: 0.090685, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 6, Time: 20.547532, Avg: 3.424589, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 3, Time: 23.595887, Avg: 7.865296, Limit: 2147483647, Count: 105097565, Valid: 1
```

### FFSTwos
```
Passes: 100000000, Time: 3.518766, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 100000000, Time: 10.000443, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 44965515, Time: 20.000000, Avg: 0.000000, Limit: 1000, Count: 168, Valid: 1
Passes: 4489940, Time: 20.000003, Avg: 0.000004, Limit: 10000, Count: 1229, Valid: 1
Passes: 422129, Time: 20.000028, Avg: 0.000047, Limit: 100000, Count: 9592, Valid: 1
Passes: 38210, Time: 20.000374, Avg: 0.000523, Limit: 1000000, Count: 78498, Valid: 1
Passes: 3412, Time: 20.001032, Avg: 0.005862, Limit: 10000000, Count: 664579, Valid: 1
Passes: 235, Time: 20.045280, Avg: 0.085299, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 7, Time: 22.450402, Avg: 3.207200, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 3, Time: 22.111328, Avg: 7.370443, Limit: 2147483647, Count: 105097565, Valid: 1
```

### FFSThrees
```
Passes: 100000000, Time: 3.557657, Avg: 0.000000, Limit: 10, Count: 4, Valid: 1
Passes: 100000000, Time: 8.163533, Avg: 0.000000, Limit: 100, Count: 25, Valid: 1
Passes: 61352678, Time: 20.000000, Avg: 0.000000, Limit: 1000, Count: 168, Valid: 1
Passes: 6577509, Time: 20.000001, Avg: 0.000003, Limit: 10000, Count: 1229, Valid: 1
Passes: 633431, Time: 20.000027, Avg: 0.000032, Limit: 100000, Count: 9592, Valid: 1
Passes: 56056, Time: 20.000087, Avg: 0.000357, Limit: 1000000, Count: 78498, Valid: 1
Passes: 4984, Time: 20.001994, Avg: 0.004013, Limit: 10000000, Count: 664579, Valid: 1
Passes: 414, Time: 20.044322, Avg: 0.048416, Limit: 100000000, Count: 5761455, Valid: 1
Passes: 8, Time: 20.087435, Avg: 2.510929, Limit: 1000000000, Count: 50847534, Valid: 1
Passes: 4, Time: 23.363038, Avg: 5.840759, Limit: 2147483647, Count: 105097565, Valid: 1
```

For some reason the original code seemed to benefit quite heavily from tuned assembly.
The FFSTwos didn't appear to benefit quite as heavily from the same option.
Its also interesting to note that the original code performed better at smaller sample sizes, however as the size grew the tables began to turn. This is likely because as you get to larger numbers, the distances between consecutive primes grows. The FFSTwos code takes advantage here as it can quickly skip across the larger gaps.
In any case the largest performance gap was from ignoring multiples of 2 and 3 from the prime sieve bitset, especially as the set grew in size.

