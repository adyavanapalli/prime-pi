# prime-pi

Benchmarking the fastest ways to compute the number of primes less than or
equal to a given positive integer, which is traditionally called the PrimePi
function.

## Sieve Methods

### Sieve of Eratosthenes

* [`naive-soe.c`](src/sieve-of-eratosthenes/naive-soe.c)
* [`odd-integers-soe.c`](src/sieve-of-eratosthenes/odd-integers-soe.c)
* [`bit-packed-odd-integers-soe.c`](src/sieve-of-eratosthenes/bit-packed-odd-integers-soe.c)

## Benchmarks

```txt
[1.00x] naive-soe                   [14.45s +- 0.03s] [BASELINE]
[3.46x] odd-integers-soe            [ 4.18s +- 0.01s]
[3.38x] bit-packed-odd-integers-soe [ 4.28s +- 0.04s]
```

Each benchmark was generated using:

```bash
$ perf stat -r 10 ...
```
