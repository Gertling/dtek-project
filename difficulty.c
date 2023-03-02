#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#include <math.h>

int delayByDifficulty()
{
    if (aiDiff == 0)
    {
        return (200 * myRandom());
    }
    else if (aiDiff == 1)
    {
        return (120 * myRandom());
    }
    else
    {
        return 0;
    }
}

int myRandom()
{

    // Use the current time as a seed for the random number generator
    unsigned int seed = TMR2;

    // Use a simple algorithm to generate a random number
    seed = (seed * 1103515245 + 12345) % (1 << 31);
    int num = (seed >> 16) % 10;

    return num;
}

double ballSpeedModifierX(double ballSpeed)
{
        if (aiDiff == 0)
    {
        return (ballSpeed * 0.5);
    }
    else if (aiDiff == 1)
    {
        return ballSpeed * 0.8;
    }
    else
    {
        return (ballSpeed * 1.5);
    }
}