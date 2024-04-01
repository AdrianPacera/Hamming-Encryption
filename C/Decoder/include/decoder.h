#ifndef DECODER_H
#define DECODER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

/*
    Function which extracts important bits
    for further fixing of corrupted data bits.
    Function doesnt serve a functional part, 
    it is used for more readable code. 
*/
void makeArraysForComparisons(uint8_t encodedByte);

/*
    Function returns a decoded part of character
    based off the encoded byte provided,as well as
    bool value to know if everything went correctly
*/
bool decodeByte(uint8_t , uint8_t*);

#endif