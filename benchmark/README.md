Benchmarks stackext for some example usages.

# Median Salary

[median_salaray_benchmark.cc](median_salary_benchmark.cc) computes the median salary of a workforce.
The function makes a function-scoped memory allocation so as to use the [std::nth_element](https://en.cppreference.com/w/cpp/algorithm/nth_element)
algorithm. The benchmark compares the performance of when the allocation is made from the heap vs
extended stack space for some random small workforces. The results I get from my machine are

```
Run on (12 X 2600 MHz CPU s)
CPU Caches:
  L1 Data 32K (x12)
  L1 Instruction 32K (x12)
  L2 Unified 256K (x12)
  L3 Unified 9216K (x12)
-------------------------------------------------------------------------
Benchmark                                  Time           CPU Iterations
-------------------------------------------------------------------------
BM_compute_median_salary_heap          84522 ns      84274 ns       6885
BM_compute_median_salary_stackext      56765 ns      56594 ns      11386
```

# Top Film
[top_film_benchmark.cc](top_film_benchmark.cc) aggregates film sales using an std::map and returns the highest grossing film.
The benchmark compares the performance of using an std::map that allocates from the heap vs an std::map that allocates from extended stack space. The results I get are

```
Run on (12 X 2600 MHz CPU s)
CPU Caches:
  L1 Data 32K (x12)
  L1 Instruction 32K (x12)
  L2 Unified 256K (x12)
  L3 Unified 9216K (x12)
--------------------------------------------------------------------
Benchmark                             Time           CPU Iterations
--------------------------------------------------------------------
BM_compute_top_film_heap         444506 ns     443801 ns       1392
BM_compute_top_film_stackext     353215 ns     352682 ns       1945
```
