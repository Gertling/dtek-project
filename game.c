#include <stdint.h>
#include <stdbool.h>
#include "header.h"


bool isPlaying = false;

double gameWidth;
double gameHeight;

double ballX;
double ballY;

double ballSpeedY = 1;
double ballSpeedX = 1;

double player1Y;
double player2Y;
double playerHeight = 5;

void initGame() // Will most likely be used to reset game
{
  isPlaying = false;

  gameWidth = 40;  // Screen width
  gameHeight = 20; // Screen height

  // Start in middle of screen
  ballX = gameWidth / 2;    // Make ball start in middle
  ballY = gameHeight / 2;   // Make ball start in middle
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

  updatePlayerPos(3, 1);
}
