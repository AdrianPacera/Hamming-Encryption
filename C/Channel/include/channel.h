#include <stdint.h>
#include <stdbool.h>

#ifndef CHANNEL_H
#define CHANNEL_h

/*
    Function is responsible for generating "noise" in byte.
    It generates random number between [0-7], which is gets
    then "flipped" in terms of its value.
*/
bool generateNoise(char , uint8_t*, int[]);

#endif