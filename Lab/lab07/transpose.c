#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // YOUR CODE HERE
    int times = n / blocksize + 1;
    for (int i = 0; i < times; i++) {
        for (int j = 0; j < times; j++) {
            for (int x = i * blocksize; x < blocksize * (i + 1); x++) {
                for (int y = j * blocksize; y < blocksize * (j + 1); y++) {
                    if (x >= n || y >= n) {
                        continue;
                    }
                    dst[y + x * n] = src[x + y * n];
                }
            }
        }
    }
}
