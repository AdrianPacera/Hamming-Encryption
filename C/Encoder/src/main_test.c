#include "unity.h"
#include "encoder.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_encodeNibbleNullValue(){
    //ARRANGE
    uint8_t *p_encodedByte = NULL;

    //ACT
    bool expectedNullHighNibble = false;
    bool actualNullHighNibble = true;

    //ASSERT
    actualNullHighNibble = encodeNibble(0,p_encodedByte);

    TEST_ASSERT_EQUAL_INT(expectedNullHighNibble, actualNullHighNibble);
}

void test_encodeNormalValues(){
    //ARRANGE
    uint8_t encodeHighNibble = 4;
    uint8_t encodedHighNibble = 0;
    uint8_t encodeLowNibble = 1;
    uint8_t encodedLowNibble = 0;

    //ACT
    bool expectedNormalValue = true;
    bool actualNormalValue = false;
    
    int expectedIntHighNibbleOutcome = 100;
    int expectedIntLowNibbleOutcome = 113;

    //ASSERT
    actualNormalValue = encodeNibble(encodeHighNibble, &encodedHighNibble);
    actualNormalValue = encodeNibble(encodeLowNibble, &encodedLowNibble);
    
    TEST_ASSERT_EQUAL_INT(expectedNormalValue, actualNormalValue);
    TEST_ASSERT_EQUAL_INT(expectedIntHighNibbleOutcome, encodedHighNibble);
    TEST_ASSERT_EQUAL_INT(expectedIntLowNibbleOutcome, encodedLowNibble);
}

void test_encodeBorderValues(){
    //ARRANGE
    uint8_t encodeHighNibbleLowBorder = 0;
    uint8_t encodedHighNibbleLowBorder = 0;
    uint8_t encodeLowNibbleLowBorder = 0;
    uint8_t encodedLowNibbleLowBorder = 0;

    uint8_t encodeHighNibbleTopBorder = 7;
    uint8_t encodedHighNibbleTopBorder = 0;
    uint8_t encodeLowNibbleTopBorder = 14;
    uint8_t encodedLowNibbleTopBorder = 0;

    //ACT
    bool expectedNormalValue = true;
    bool actualNormalValue = false;
    
    int expectedIntHighNibbleOutcomeLowBorder = 0;
    int expectedIntLowNibbleOutcomeLowBorder = 0;

    int expectedIntHighNibbleOutcomeTopBorder = 39;
    int expectedIntLowNibbleOutcomeTopBorder = 14;

    //ASSERT
    actualNormalValue = encodeNibble(encodeHighNibbleLowBorder, &encodedHighNibbleLowBorder);
    actualNormalValue = encodeNibble(encodeLowNibbleLowBorder, &encodedLowNibbleLowBorder);

    actualNormalValue = encodeNibble(encodeHighNibbleTopBorder, &encodedHighNibbleTopBorder);
    actualNormalValue = encodeNibble(encodeLowNibbleTopBorder, &encodedLowNibbleTopBorder);
    
    TEST_ASSERT_EQUAL_INT(expectedNormalValue, actualNormalValue);

    TEST_ASSERT_EQUAL_INT(expectedIntHighNibbleOutcomeLowBorder, encodedHighNibbleLowBorder);
    TEST_ASSERT_EQUAL_INT(expectedIntLowNibbleOutcomeLowBorder, encodedLowNibbleLowBorder);

    TEST_ASSERT_EQUAL_INT(expectedIntHighNibbleOutcomeTopBorder, encodedHighNibbleTopBorder);
    TEST_ASSERT_EQUAL_INT(expectedIntLowNibbleOutcomeTopBorder, encodedLowNibbleTopBorder);
}
int main(void)
{
    UnityBegin(0);

    //RUN TESTS
    RUN_TEST(test_encodeNibbleNullValue, 1);
    RUN_TEST(test_encodeNormalValues, 2);
    RUN_TEST(test_encodeBorderValues, 3);

    return UnityEnd();
}