#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void displayPlayer(int playerNumber, int posY)
{
    int x;
    if (playerNumber == 1)
    {
        x = 1;
    }
    else if (playerNumber == 2)
    {
        x = 123;
    }
    else
    {
    }
    int i;
    for (i = 0; i < playerHeight; i++)
    {
        enablePixel(x, posY + i);
        enablePixel(x + 1, posY + i);
        enablePixel(x + 2, posY + i);
    }
}

void displayBall(int posX, int posY) 
{
    int size = getBallSize();
    int i;
    for (i = 0; i < size; i++)
    {
        int j;
        for (j = 0; j < size; j++)
        {
            enablePixel(posX + i, posY + j);
        }
    }
}

