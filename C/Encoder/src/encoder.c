#include <stdbool.h>
#include "encoder.h"

//masks for getting the parity bits
//each mask has a set on position
//where we care to know whether the bit
//is set or cleared in the provided nibble
const uint8_t maskPB0 = 0b00001011;
const uint8_t maskPB1 = 0b00000111;
const uint8_t maskPB2 = 0b00001101;

//storing the parity bit masks
uint8_t parityBitsMasks[3] = {maskPB2, maskPB1, maskPB0}; 

uint8_t countSetsInNibble(uint8_t byte){  
    //variable initialization  
    int countOfSets = 0x0;

    //checking if bit is set on every position in nibble
    for(int position=4; position>=0; position--){
        
        //if byte on desired position is set
        //increment count of sets
        if((byte>>position) & 0x01){
            countOfSets++;
        }
    }
    return countOfSets;
}


void getParityBit(uint8_t* parityBits, uint8_t nibble, uint8_t parityBitMask){
    //comparing nibble with parity mask to get the amout of sets in nibble about
    //which we care about. E.g. to get parity bit 0, we care about the sets and 
    //clears on bit positions  0, 1, 3 and so on with other parity bits.
    uint8_t importantSetsInNibbleByte = (nibble & parityBitsMasks[parityBitMask]);

    //counting the amount of important sets in nibble which we got in previous line
    int numOfSetsInNibble = countSetsInNibble(importantSetsInNibbleByte);

    //pre-shifitng the variable containing the parity bits to ensure
    //that the parity bit gets assign to a correct location
    *parityBits <<= 1; 

    //deciding the whether to set or clear a parity bit based off the number of
    //sets in nibble, even number of sets means that the parity bits needs to be 
    //cleared and vice versa
    if(numOfSetsInNibble & (numOfSetsInNibble &0x01)){ 
        *parityBits |= 1;
    }
    else{
        *parityBits |= 0;           
    }
}

bool encodeNibble(uint8_t nibble, uint8_t* encodedByteForNibble){
    //chcecking if valid pointer was passed to the function
    if(encodedByteForNibble == NULL){
        return false;
    }
    uint8_t parityBits = 0;

    //calling the functions for getting the parity bit 
    //last argument represents the parity mask index,
    //which is stored in the array of parity masks
    getParityBit(&parityBits, nibble, 0);
    getParityBit(&parityBits, nibble, 1);
    getParityBit(&parityBits, nibble, 2);

    //shifting the parity bits to the position of high nibble
    //to then compare it with previous high nibble, which in 
    //this case becomes the low nibble
    parityBits <<= 4; 
    *encodedByteForNibble = parityBits | nibble;

    return true;
}