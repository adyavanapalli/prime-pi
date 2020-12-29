// odd-integers-soe.c

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

/**
 * To better understand this implementation, please see naive-soe.c.
 */

uint64_t prime_pi(size_t n)
{
    // We include only the odd integers in our sieve i.e. 1, 3, 5, ... <= n,
    // hence the ith index corresponds with an integer with value 2 * i + 1.
    // Since calloc initializes all the allocated memory to 0, we can think of
    // sieve[i] == false as indicating (2 * i + 1) is a prime number.
    bool* sieve = calloc((n + 1) / 2, sizeof(bool));


    // For the first loop, we need only iterate through the primes from 3 to
    // ceil(sqrt(n)) because the primes between ceil(sqrt(n)) (inclusive) and n
    // (inclusive) cannot sieve numbers between ceil(sqrt(n)) (inclusive) and n
    // (inclusive) because those numbers would have been already sieved out by
    // the smaller prime numbers.
    for (size_t i = 3; i * i <= n; i += 2)
    {
        // If we encounter a prime number, we start the sieving procedure.
        if (!sieve[i / 2])
        {
            // Give our prime number a better label.
            size_t p = i;

            // Given a prime p, we should start sieving from the _next_ odd
            // multiple of it starting from p i.e. p * p, p * (p + 2), p * (p +
            // 4), p * (p + 6), ... <= n.
            for (size_t j = p * p; j <= n; j += 2 * p)
            {
                sieve[j / 2] = true;
            }
        }
    }

    // Since we skipped counting the even primes (there is only 1 i.e. 2), we
    // should include it in our count.
    uint64_t prime_count = 1;

    for (size_t i = 3; i <= n; i += 2)
    {
        if (!sieve[i / 2])
        {
            prime_count++;
        }
    }

    free(sieve);

    return prime_count;
}

int main(int argc, char *argv[])
{
    // If no value is provided, use the default value for n i.e. in PrimePi(n).
    size_t n = DEFAULT_N;

    if (argc == 2)
    {
        n = strtoul(argv[1], NULL, BASE_10);
    }

    uint64_t prime_count = prime_pi(n);

    printf("prime_pi(%lu): %lu\n", n, prime_count);

    return 0;
}
