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
        x = 125;
    }
    else
    {
        // Idiot
    }
    int i;
    for (i = 0; i < playerHeight; i++)
    {
        enablePixel(x, posY + i);
        enablePixel(x + 1, posY + i);
    }
}

void displayBall(int posX, int posY)
{
    enablePixel(posX, posY);
    enablePixel(posX + 1, posY);

    enablePixel(posX, posY + 1);
    enablePixel(posX + 1, posY + 1);
}

void displayGame(void)
{
}