// popcnt_native_vs_array.c

#include <assert.h>
#include <errno.h>
#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int main()
{
    __m128 a4 = _mm_set_ps(4.0f, 4.1f, 4.2f, 4.3f);
    __m128 b4 = _mm_set_ps(1.0f, 1.0f, 1.0f, 1.0f);

    __m128 c4 = _mm_add_ps(a4, b4);

    return 0;
}
