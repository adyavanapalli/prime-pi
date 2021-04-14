// naive-divisibility.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

uint64_t prime_pi(size_t n)
{
    uint64_t prime_count = n - 1;

    for (size_t i = 2; i <= n; i++)
    {
        for (size_t j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                prime_count--;
                break;
            }
        }
    }

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
