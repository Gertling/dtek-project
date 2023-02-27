#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#include <math.h>

bool isPlaying = false;

double gameWidth;
double gameHeight;

double ballX;
double ballY;

double ballSpeedY = 0.2;
double ballSpeedX = 0.2;

double player1Y;
double player2Y;

double playerHeight = 5;

void initGame() // Will most likely be used to reset game
{
  playerHeight = 8;
  player1Y = 15;
  isPlaying = false;

  gameWidth = 128; // Screen width
  gameHeight = 32; // Screen height

  // Start in middle of screen
  ballX = gameWidth / 2;  // Make ball start in middle
  ballY = gameHeight / 2; // Make ball start in middle
}

void containPlayer(double *playerPointer, double upperLimit)
{
  if (*playerPointer > upperLimit)
  {
    *playerPointer = upperLimit;
  }
  else if (*playerPointer < 0)
  {
    *playerPointer = 0;
  }
}

void updatePlayerPos(double offset, int playerNumber)
{
  if (playerNumber == 1)
  {
    player1Y += offset;
    containPlayer(&player1Y, gameHeight - playerHeight);
  }
  else if (playerNumber == 2)
  {
    player2Y += offset;
    containPlayer(&player2Y, gameHeight - playerHeight);
  }
  else
  {
    // Not valid player number
  }
}

void startGame()
{
  isPlaying = true;
}

void tickGame()
{
  ballBounce();
  updateBallPos();
}

int myRound(double number)
{
  int rounded = floor(number);
  if (number - rounded >= 0.5)
  {
    return rounded + 1;
  }
  else
  {
    return rounded;
  }
}
void updateBallPos()
{
  ballX += ballSpeedX;
  ballY += ballSpeedY;
}

int getBallPositionY()
{
  return myRound(ballY);
}
int getBallPositionX()
{
  return myRound(ballX);
}

int ballBounce()
{
  if (ballY + 1 > gameHeight - 1)
  {
    ballSpeedY = -1 * fabs(ballSpeedY);
  }
  if (ballY < 0)
  {
    ballSpeedY = fabs(ballSpeedY);
  }

  if (ballX < 0)
  {
    ballSpeedX = 1 * fabs(ballSpeedX);
  }
  if (ballX + 1 > gameWidth - 1)
  {
    ballSpeedX = -1 * fabs(ballSpeedX);
  }
}

int getPlayerPosition(int playerNumber)
{
  if (playerNumber == 1)
  {
    int player1 = myRound(player1Y); // Player position as int.
    return player1;
  }
  if (playerNumber == 2)
  {

    int player2 = myRound(player2Y); // Player position as int.
    return player2;
  }
}
