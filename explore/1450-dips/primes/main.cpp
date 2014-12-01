// Demo for printf over the serial port, generating half a million primes.
// See http://jeelabs.org/2014/12/10/dips-into-the-lpc810/

#include <stdint.h>
#include <stdio.h>

#if __arm__
#include "serial.h"
#endif
uint16_t factors [400]; // prime factors to check against

int main () {
#if __arm__
    LPC_SWM->PINASSIGN0 = 0xFFFF0004UL;
    serial.init(LPC_USART0, 115200);
#endif
    printf("Prime numbers:\n");

    uint32_t limit = 3, numFactors = 0, width = 0, numPrimes = 0;

    for (int value = 2; value < limit; ++value) {
        int i;
        for (i = 0; i < numFactors; ++i)
            if (value % factors[i] == 0) // check divisibility
                break;
        if (i < numFactors)
            continue; // found a factor, so it's not prime
        ++numPrimes;

        int chars = printf(" %d", value);

        width += chars; // wrap lines to under 80 chars
        if (width + chars >= 80) {
            width = 0;
            printf("\n");
        }

        if (numFactors >= sizeof factors / sizeof factors[0])
            continue; // no more room left in the factors table

        factors[numFactors] = value;
        if (factors[numFactors] != value)
            continue; // whoops, it got truncated
        ++numFactors;

        limit = value * value; // largest prime we can check for
    }

    printf("\nFound %d primes.\n", numPrimes);
    return 0;
}