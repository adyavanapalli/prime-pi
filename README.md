# prime-pi

Benchmarking the fastest ways to compute the number of primes less than or
equal to a given positive integer, which is traditionally called the PrimePi
function.

## Sieve Methods

### Sieve of Eratosthenes

* [`naive-soe.c`](src/sieve-of-eratosthenes/naive-soe.c)
* [`odd-integers-soe.c`](src/sieve-of-eratosthenes/odd-integers-soe.c)

## Benchmarks

```txt
[1.00x] naive-soe        [14.51s +- 0.05s] [BASELINE]
[3.45x] odd-integers-soe [ 4.21s +- 0.01s]
```

Each benchmark was generated using:

```bash
$ perf stat -r 10 ...
```
