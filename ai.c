#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#include <math.h>

int targetY;

void aiHandler()
{

    if ((getPlayerPosition(2)) + (playerHeight / 2) < targetY)
    {
        updatePlayerPos(0.2, 2);
    }
    else if (getPlayerPosition(2) + (playerHeight / 2) > targetY)
    {
        updatePlayerPos(-0.2, 2);
    }
}

void calculateBallImpact()
{
    double t = (123 - getBallPositionX() - getBallSize()) / ballSpeedX;

    double dist = ballSpeedY > 0 ? (28 - getBallPositionY()) : getBallPositionY();
    
    

    double dBY = fabs(ballSpeedY) * t;

    double O = ((int)(dBY - dist) % (int)(32 - getBallSize())); // HAve to cast to ints... fmod are not avail.

    double bouncesAmount = ((dBY - dist) / (32 - (getBallSize()))) + 1; // Amount of times the ball bounces

    PORTE = (int)dist;
    if (ballSpeedY > 0)
    {
        if (((int)floor(bouncesAmount) % 2) == 0)
        {
            targetY = O;
        }
        else
        {
            targetY = 28 - O;
        }

        PORTE |= 128;
    }
    else
    {
        if (((int)floor(bouncesAmount) % 2) != 0)
        {
            targetY = O;
        }
        else
        {
            targetY = 28 - O;
        }
        PORTE |= 64;
    }
}