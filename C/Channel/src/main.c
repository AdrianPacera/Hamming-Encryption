#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "channel.h"

//Function creates a histogram in terminal to show the user how
//many times each bit has been flipped 
void createHistogram(int arrayOfCountersForFlippeBits[]){
    printf("==========================\n");
    printf("Histogram of flipped bits:\n");

    //printing out the counters for each bit
    for(int i = 0; i<8; i++){
        printf("Bit %d flipped: %d times\n", i, arrayOfCountersForFlippeBits[i]);
    }
    printf("==========================\n");
}

//function for reading an input file and writing into
//encoded nibbles into provided .bin file
void simulateMediumCorruption(FILE* inputFile, FILE* transmittedData){
    //variables initialization
    char readCharacterBin;
    uint8_t corruptedByte = 0;
    int arrayOfCountersForFlippeBits[8] = {0};

    //reading the input file character by character
    while((readCharacterBin = fgetc(inputFile)) != EOF){
        bool byteCorruption = false; 

        //encode the byte read
        byteCorruption = generateNoise(readCharacterBin, &corruptedByte, arrayOfCountersForFlippeBits);

        //checker for correct noise generation
        if((byteCorruption) == true){
            //write encoded byte to the .bin output file
            fputc(corruptedByte, transmittedData);
        }
        else{
            printf("There happened to be a problem corrupting character!");
        }
    }

    //creating the histogram of counters for flipped bits
    createHistogram(arrayOfCountersForFlippeBits);
}


int main(int argc, char const *argv[])
{
    //cmd for opening files: .\output\main.exe encodedData.bin transmittedData.bin

    //implement a random seed for the "random" start of number reading
    srand(time(0)); 
    
    //checker if correct amount of arguments were provided by user
    if(argc != 3){
        printf("Invalid number of input files");
        return 1;
    }

    //initializing FileIO
    FILE* encodedData  = fopen(argv[1], "r");
    FILE* decodedData = fopen(argv[2], "w");

    //checking pointers validity
    if ((encodedData  == NULL) || (decodedData == NULL)){
        printf("Failed to open one of the files.\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Files loaded successfully.\n");
    }
    
    //reading a provided file and writing decoded data
    //into the provided output file
    simulateMediumCorruption(encodedData , decodedData);

    //closing the files
    fclose(encodedData);
    fclose(decodedData);

    return 0;
}
