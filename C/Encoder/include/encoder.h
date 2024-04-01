
#ifndef ENCODER_H
#define ENCODER_H
#include <stdint.h>
#include <stdbool.h>

/*
    Function which servers to count an amount of sets in a 
    provided nibble.
*/
uint8_t countSetsInNibble(uint8_t byte);

/*
    Function is respponsible for setting or clearing a parity bit
    on a specific location. For getting 4-3 ratio of of nibble to parity
    bits (case for one error correction), this function has to be called
    at least 3 times, for getting each parity bit. 
*/
void getParityBit(uint8_t* parityBits, uint8_t nibble, uint8_t parityBitMask);

/*
    Function is responsible for getting the correct parity bits
    for a provided nibble. The parity bits are stored in the
    variable "parityBits".
*/
bool encodeNibble(uint8_t nibble, uint8_t* encyptedByteForNibble);

#endif