#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

uint16_t get_bit(uint16_t x, unsigned n) {
    return (x >> n) & 1;
}

void set_bit(uint16_t * x, unsigned n, unsigned v) {
    uint16_t temp = *x;
    uint16_t maskToZero = 1U << n;
    maskToZero = ~(maskToZero);
    temp = temp & maskToZero;
    uint16_t mask = v << n;
    temp = temp | mask;
    *x = temp;
}

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t temp = *reg;
    uint16_t x0 = get_bit(temp, 0);
    uint16_t x2 = get_bit(temp, 2);
    uint16_t x3 = get_bit(temp, 3);
    uint16_t x5 = get_bit(temp, 5);
    unsigned newBit = x5 ^ (x3 ^ (x2 ^ x0));
    temp = temp >> 1;
    set_bit(&temp, 15, newBit);
    *reg = temp;

}

