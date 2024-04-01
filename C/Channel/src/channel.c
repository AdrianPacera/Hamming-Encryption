#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "channel.h"

#define TOP_NUM_BOUNDRY 7
#define BOTTOM_NUM_BOUNDRY 0


bool generateNoise(char readCharacterBin, uint8_t* corruptedByte, int arrayOfCountersForFlippeBits[]){
    //checking whether a valid pointers were passed to the function
    if((corruptedByte == NULL) || (arrayOfCountersForFlippeBits == NULL)){
        return false;
    }
    
    //taking a random position for bit
    int positionForBitFlip = (rand() % (TOP_NUM_BOUNDRY+1));

    //toggling the bit in provided byte in randomly generated bit location
    readCharacterBin ^= (1<<positionForBitFlip);

    //incrementing the counter for flipped bit in byte
    arrayOfCountersForFlippeBits[positionForBitFlip]++;

    //storing the corrupted byte into return variable which
    //gets written into the file
    *corruptedByte = readCharacterBin;

    return true;
}