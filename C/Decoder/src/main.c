
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "decoder.h"

//function for reading an input file and writing into
//file with corrected decoded data
void readInputFileAndWriteEncodedData(FILE* transmittedData, FILE* decodedData){
    //variables initialization
    uint16_t encodedCharAsInt = 0;
    uint8_t encodedHighByte = 0;
    uint8_t encodedLowByte = 0;
    char decodedChar = 0;

    //reading the input file by 2 bytes at time (size of encoded character)
    //until the fread returns 1, which the function is returning until it reaches
    //the end, in that case the function returns a -1.
    while(fread(&encodedCharAsInt, sizeof(encodedCharAsInt), 1 ,transmittedData) == 1){
        //initializing variables used
        bool validDecodedByteHigh = false;
        bool validDecodedByteLow = false;
        uint8_t firstPartOfChar = 0;
        uint8_t secondPartOfChar = 0;

        //splitting the encoded bytes into 2 separate bytes
        encodedHighByte = encodedCharAsInt;
        encodedLowByte = (encodedCharAsInt >> 8); 
        
        //test values
        //encodedHighByte= 0x64;
        //encodedLowByte = 0x71;

        //decode the bytes
        validDecodedByteHigh = decodeByte(encodedHighByte, &firstPartOfChar);
        validDecodedByteLow = decodeByte(encodedLowByte, &secondPartOfChar);

        //chcecking if the decoding went correctly
        if((validDecodedByteHigh & validDecodedByteLow) == true){
            //combine decoded bytes's nibbles into one byte
            decodedChar = (firstPartOfChar <<4) | secondPartOfChar;
            //write decoded char to the .txt file
            fputc(decodedChar, decodedData);
        }
        else{
            printf("There happened to be a problem in decoding one of the bytes!");
        }
    }
}

int main(int argc, char const *argv[])
{
    //cmd for opening files: .\output\main.exe transmittedData.bin decodedData.txt

    //checker if correct amount of arguments were provided by user
    if(argc != 3){
        printf("Invalid number of input files");
        return 1;
    }

    //initializing FileIO
    FILE* transmittedData  = fopen(argv[1], "r");
    FILE* decodedData = fopen(argv[2], "w");

    //checking pointers validity
    if ((transmittedData  == NULL) || (decodedData == NULL)){
        printf("Failed to open one of the files.\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Files loaded successfully.\n");
    }
    
    //reading a provided file and writing decoded data
    //into the provided output file
    readInputFileAndWriteEncodedData(transmittedData , decodedData);
    

    //closing the files
    fclose(transmittedData);
    fclose(decodedData);

    return 0;
}