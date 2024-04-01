#include <stdbool.h>
#include "unity.h"
#include "unity.h"
#include "decoder.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_decodeByteNullValues(){
    //ARRANGE
    uint8_t *p_resultByteNull = NULL;
    uint8_t encodedByte = 0;

    //ACT    
    bool expectedResultByteNull = false;
    bool actualResultByteNull = true;

    //ASSERT
    actualResultByteNull = decodeByte(encodedByte, p_resultByteNull);

    TEST_ASSERT_EQUAL_INT(expectedResultByteNull, actualResultByteNull);
}

void test_decodeUncorruptedValues(){
    //ARRANGE
    uint8_t encodedByteHigh = 0x64;
    uint8_t encodedByteLow = 0x71;
    uint8_t decodedByteHigh = 0; 
    uint8_t decodedByteLow = 0;

    //ACT
    bool expectedNormalValue = true;
    bool actualNormalValue = false;
    
    uint8_t expectedHighByteOutcome = 0x04;
    uint8_t expectedLowByteOutcome = 0x01;

    //ASSERT
    actualNormalValue = decodeByte(encodedByteHigh, &decodedByteHigh);
    actualNormalValue = decodeByte(encodedByteLow, &decodedByteLow);

    TEST_ASSERT_EQUAL_INT(expectedNormalValue, actualNormalValue);
    TEST_ASSERT_EQUAL_INT(expectedHighByteOutcome, decodedByteHigh);
    TEST_ASSERT_EQUAL_INT(expectedLowByteOutcome, decodedByteLow);
}

void test_decodeCorruptedValues(){
    //ARRANGE
    uint8_t encodedHighByteCorrupted = 0x65; //Databit 0 corrupted
    uint8_t encodedLowByteCorrupted  = 0x73; //Databit 1 corrupted
    uint8_t decodedHighByteCorrupted  = 0;
    uint8_t decodedLowByteCorrupted  = 0; 

    //ACT
    bool expectedNormalValue = true;
    bool actualNormalValue = false;
    
    uint8_t expectedDecodedHighByteOutcome = 0x04; 
    uint8_t expectedDecodedLowByteOutcome = 0x01;

    //ASSERT 
    actualNormalValue = decodeByte(encodedHighByteCorrupted, &decodedHighByteCorrupted);
    actualNormalValue = decodeByte(encodedLowByteCorrupted, &decodedLowByteCorrupted);
    
    TEST_ASSERT_EQUAL_INT(expectedNormalValue, actualNormalValue);
    TEST_ASSERT_EQUAL_INT(expectedDecodedHighByteOutcome, decodedHighByteCorrupted);
    TEST_ASSERT_EQUAL_INT(expectedDecodedLowByteOutcome, decodedLowByteCorrupted);
}

int main(void)
{
    UnityBegin(0);

    //RUN TESTS
    RUN_TEST(test_decodeByteNullValues,1 );
    RUN_TEST(test_decodeUncorruptedValues, 2);
    RUN_TEST(test_decodeCorruptedValues, 3);

    return UnityEnd();
}