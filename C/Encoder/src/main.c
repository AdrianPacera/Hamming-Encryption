
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "encoder.h"

//function for reading an input file and writing into
//encoded nibbles into provided .bin file
void readInputFileAndWriteEncodedData(FILE* inputFile, FILE* encodedData){
    //variables initialization
    char readCharacter;
    uint8_t encodeHighNibble = 0;
    uint8_t encodeLowNibble = 0;

    uint8_t encodedByteForHighNibble = 0;
    uint8_t encodedByteForLowNibble = 0;

    //reading the input file character by character
    while((readCharacter = fgetc(inputFile)) != EOF){
        bool validEncodedHighNibble = false;
        bool validEncodedLowNibble = false;
        //splitting the character read into nibbles
        encodeHighNibble = (readCharacter >> 4);
        encodeLowNibble = (readCharacter & 0x0F); 

        //encode the nibbles
        validEncodedHighNibble = encodeNibble(encodeHighNibble, &encodedByteForHighNibble);
        validEncodedLowNibble = encodeNibble(encodeLowNibble, &encodedByteForLowNibble);

        if((validEncodedHighNibble & validEncodedLowNibble) == true){
            //write encoded nibbles to the .bin file
            fputc(encodedByteForHighNibble, encodedData);
            fputc(encodedByteForLowNibble, encodedData);
        }
        else{
            printf("There happened to be a problem encoding character!");
        }
    }
}

int main(int argc, char const *argv[])
{
    //cmd for opening file: .\output\main.exe inputData.txt encodedData.bin

    //checker if correct amount of arguments were provided by user
    if(argc != 3){
        printf("Invalid number of input files");
        return 1;
    }

    //initializing FileIO
    FILE* inputFile = fopen(argv[1], "r");
    FILE* encodedData = fopen(argv[2], "w");

    //checking pointers validity
    if ((inputFile == NULL) || (encodedData == NULL)){
        printf("Failed to open one of the files.\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Files loaded successfully.\n");
    }
    
    //reading a provided file and writing encoded data
    //into the provided output file
    readInputFileAndWriteEncodedData(inputFile, encodedData);
    

    //closing the files
    fclose(inputFile);
    fclose(encodedData);

    return 0;
}
