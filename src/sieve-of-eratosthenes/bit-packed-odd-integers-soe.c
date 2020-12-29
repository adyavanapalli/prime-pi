// bit-packed-odd-integers.c

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

/**
 * To better understand this implementation, please see odd-integers-soe.c.
 */

uint64_t COUNT_UNSET_BITS[] =
{
    8, 7, 7, 6, 7, 6, 6, 5, 7, 6, 6, 5, 6, 5, 5, 4,
    7, 6, 6, 5, 6, 5, 5, 4, 6, 5, 5, 4, 5, 4, 4, 3,
    7, 6, 6, 5, 6, 5, 5, 4, 6, 5, 5, 4, 5, 4, 4, 3,
    6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
    7, 6, 6, 5, 6, 5, 5, 4, 6, 5, 5, 4, 5, 4, 4, 3,
    6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
    6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
    5, 4, 4, 3, 4, 3, 3, 2, 4, 3, 3, 2, 3, 2, 2, 1,
    7, 6, 6, 5, 6, 5, 5, 4, 6, 5, 5, 4, 5, 4, 4, 3,
    6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
    6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
    5, 4, 4, 3, 4, 3, 3, 2, 4, 3, 3, 2, 3, 2, 2, 1,
    6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
    5, 4, 4, 3, 4, 3, 3, 2, 4, 3, 3, 2, 3, 2, 2, 1,
    5, 4, 4, 3, 4, 3, 3, 2, 4, 3, 3, 2, 3, 2, 2, 1,
    4, 3, 3, 2, 3, 2, 2, 1, 3, 2, 2, 1, 2, 1, 1, 0
};

uint64_t prime_pi(size_t n)
{
    // We include only the odd integers in our sieve i.e. 1, 3, 5, ... <= n.
    // Additionally, we use a bit-array to store the primality of each integer.
    // Hence, byte 0 might resemble 0b1001_000X i.e. bit 1, 2, 3, 5, and 6
    // correspond with 3, 5, 7, 11, and 13 are primes (and 9 and 15 are
    // non-prime).
    uint8_t* sieve = calloc((n + 15) / 16, sizeof(uint8_t));

    // Each odd integer's primality value exists at a specific byte and bit
    // index in our bit-array. For the odd integers 1 -> 15, 17 -> 31, ...
    // (inclusive), we may obtain their bit index by first mapping their values
    // to a shifted bit index (one where bit indexes range from 0 to (n + 1) /
    // 2) and then by taking the value modulo 8. Hence, we have an odd integer i
    // placed at shifted bit index (i + 1) / 2, or equivalently floor(i / 2)
    // (since i is always odd) and bit index floor(i / 2) % 8. The byte index
    // is obtained more easily by dividing by 16 (and taking the floor) i.e.
    // floor(i / 16).

    #define BIT_INDEX(i) (i / 2)
    #define BIT_INDEX_IN_BYTE(i) (BIT_INDEX(i) % 8)
    #define BYTE_INDEX(i) (i / 16)

    // To determine whether the kth bit in a given byte is unset, we can AND the
    // byte with a mask having the kth bit set and check if the byte & MASK(k)
    // is indeed 0.

    #define MASK(i) (0x1 << i)
    #define IS_BIT_UNSET(sieve, i) ((sieve[BYTE_INDEX(i)] & MASK(BIT_INDEX_IN_BYTE(i))) == 0x0)

    // To set to bit, we just OR the mask.
    #define SET_BIT(sieve, i) (sieve[BYTE_INDEX(i)] |= MASK(BIT_INDEX_IN_BYTE(i)))

    for (size_t i = 3; i * i <= n; i += 2)
    {
        // If we encounter a prime number, we start the sieving procedure.
        if (IS_BIT_UNSET(sieve, i))
        {
            // Give our prime number a better label.
            size_t p = i;

            // Given a prime p, we should start sieving from the _next_ odd
            // multiple of it starting from p i.e. p * p, p * (p + 2), p * (p +
            // 4), p * (p + 6), ... <= n.
            for (size_t j = p * p; j <= n; j += 2 * p)
            {
                SET_BIT(sieve, j);
            }
        }
    }

    // Since we skipped counting the even primes (there is only 1 i.e. 2), we
    // should include it in our count.
    uint64_t prime_count = 1;

    for (size_t i = 0; i < (n + 15) / 16; i++)
    {
        prime_count += COUNT_UNSET_BITS[sieve[i]];
    }

    free(sieve);

    // Before we return the count, we need to adjust the count for two things:

    // 1. Bit 0, corresponding to the integer with value 1, must be discounted.
    prime_count--;

    // 2. When we initialized the sieve, we initialized primality values for (8
    // * floor((n + 15) / 16)) integers, which could be different from the
    // number of integers we're attempting to count for primality floor((n +
    // 1) / 2). So we should substract the excess.
    prime_count -= 8 * ((n + 15) / 16) - ((n + 1) / 2);

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
