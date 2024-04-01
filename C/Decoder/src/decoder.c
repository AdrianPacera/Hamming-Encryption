#include <stdbool.h>
#include "decoder.h"
#define D0 0
#define D1 1 
#define D2 2
#define D3 3
#define misMatchInBits_P0P1P2 0b111
#define misMatchInBits_P0P1 0b110
#define misMatchInBits_P1P3 0b101
#define misMatchInBits_P1P2 0b011

//declaring the arrays used 
uint8_t parityBitValue[3];
uint8_t recalculationOfParityBits[3];

/*
    This function is responsible for making an
    array of values important for the detecting 
    the corrupted error. The filling up of arrays
    with sole parity bits as well as result value
    of intersection of the data bits is done in 
    this function. Esecially the function servers
    for readability sake, and not functional one.
*/
void makeArraysForComparisons(uint8_t encodedByte){
    //extracting the parity bits from the byte and storing them in the array
    parityBitValue[0] = (encodedByte >> 4) & 0x01; //parity bit P0
    parityBitValue[1] =  (encodedByte >> 5) & 0x01; //parity bit P1
    parityBitValue[2] = (encodedByte >> 6) & 0x01; //parity bit P2

    //extracting the data bits from the byte
    uint8_t databit_D0 = encodedByte & 0x01;
    uint8_t databit_D1 = (encodedByte >> 1) & 0x01;
    uint8_t databit_D2 = (encodedByte >> 2) & 0x01;
    uint8_t databit_D3 = (encodedByte >> 3) & 0x01;

    //getting the values of intesectrions of the data bits and storing them in the array
    recalculationOfParityBits[0] = (databit_D3^databit_D1^databit_D0); //Intesection of data bit values in first set (circle 1)
    recalculationOfParityBits[1] = (databit_D2^databit_D1^databit_D0); //Intesection of data bit values in second set (circle 2)
    recalculationOfParityBits[2] = (databit_D3^databit_D2^databit_D0); //Intesection of data bit values in third set (circle 3)
}

/*  
    Function is responsible for decoding a provided byte.
    This functrion first creates an array of values which 
    are used for comparison. 
*/
bool decodeByte(uint8_t encodedByte, uint8_t* decodedByte){
    //checking if valid pointer were passed to the function
    if((decodedByte == NULL)){
        return false;
    }

    //variables used for correcting the corrupted data bit
    uint8_t comparisonMisMatchPattern = 0;
    int misMatchCounter = 0;

    /*
        Making an arrays of parity bits and the values from
        the intersection of all data bits. This is done to 
        then compare if the values of comparisons fit with 
        each other 
    */
    makeArraysForComparisons(encodedByte);
    
    /*
        The comparison is made by comparing
        the values of parity bits with the value of intersections
        of data bits. If the comparison is correct (parity bit value 
        is equal to the intersection of data bit values), a 0 is added
        to the variable "comparisonMisMatchPattern", to represent equality.
        If the comparison is not equal, 1 is added to the variable to
        represent a mismatch in parity bit with its assigned data bits.
    */
    for(int i =0; i<3; i++){
        comparisonMisMatchPattern <<= 1;
        if(parityBitValue[i] != recalculationOfParityBits[i]){
            comparisonMisMatchPattern |= 1;
            misMatchCounter++;
        }
        else{
            comparisonMisMatchPattern |= 0;
        }
    }

    /*
        Chcecking for a mistake pattern which has appeared.
        First check is to determine whether the amount of mistakes
        made is above or equal to 2. This number represents the 
        amount of unmatches in the comparison, and if its bigger
        or equal to 2, it means that 2 or more parity bits are not
        matching their data bit intersection values. This means that
        a data bit has been corrupted (analogy derived from the parity
        bit relation to the data bits). 

        The following checkers are based of the patters of mis-matching
        comparisons. For example if parity bits 0 and 1 are not matching
        their data bit intersection values, the pattern of the variable
        "comparisonMisMatchPattern" is 110 (representing the incorrect values
        of parity bits with 1 and correct value with 0). This pattern is 
        always the same, no matter the actual values of data/parity bits.
        One more example is if data bit 0 has been corrupted, none of the
        parity bits will match, resulting in the value of "comparisonMisMatchPattern"
        being 111. 
    */
    if(misMatchCounter>=2){
        //toggling the corrupted data bit based off the comparisonMisMatchPattern 
        //the encoded byte gets XOR-ed with itself and 1 shifted to the position 
        //of corrupted bit, by this we "switch" or "toggle" the bit value. E.g.
        //corrupted bit is 0, the XOR will toggle the bit number to 1 and vice versa.
        switch (comparisonMisMatchPattern)
        {
        case misMatchInBits_P0P1P2:
            encodedByte ^= (1<<D0);
            break;
        case misMatchInBits_P0P1:
            encodedByte ^= (1<<D1);
            break;
        case misMatchInBits_P1P2:
            encodedByte ^= (1<<D2);
            break;
        case misMatchInBits_P1P3:
            encodedByte ^= (1<<D3);
            break;
        default:
            break;
        }
    }

    //getting rid of the redundant parity bits
    *decodedByte = encodedByte & 0x0F;

    return true;
}