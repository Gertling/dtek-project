#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#include <math.h>


bool serveDelay = true;
bool isPlaying = false;

double gameWidth;
double gameHeight;

double ballSize = 4;

double ballX;
double ballY;

double ballSpeedY = 0.2;
double ballSpeedX = 0.25;
double player1Y;
double player2Y;

double playerHeight;

bool getServeDelay(){
  return serveDelay;
}

void setServeDelay(bool b){
  serveDelay = b;
}


int getBallSize()
{
  return ballSize;
}



void initGame() // Will most likely be used to reset game
{
  playerHeight = 12;
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
  if (isPlaying)
  {
    paddleCollide();
    ballBounce();
    updateBallPos();
  }
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
  if ((ballY + ballSize) > gameHeight - 1)
  {
    ballSpeedY = -1 * fabs(ballSpeedY);
  }
  if (ballY < 0)
  {
    ballSpeedY = fabs(ballSpeedY);
  }

  if (ballX < 0)
  {
    onGoal(1);
    // scorePlayerOne++;
  }
  if ((ballX + ballSize) > gameWidth - 1)
  {
    onGoal(2);
    // scorePlayerTwo++;
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

void onGoal(int playerNumber)
{
  serveDelay = true;
  isPlaying = false;
  ballX = gameWidth / 2;  // Make ball start in middle
  ballY = gameHeight / 2; // Make ball start in middle

  ballSpeedY = 0.2;
  ballSpeedX = 0.25; // Give ball it's beginning direction and speed
}

void paddleCollide()
{
  if (player1Y <= (ballY + ballSize) && ballY <= (player1Y + 8) && ballX <= 4)
  {
    ballSpeedX = fabs(ballSpeedX);
    collisionDeflection(player1Y);
  }
  else if (player2Y <= (ballY + ballSize) && ballY <= (player2Y + 8) && ((ballX + ballSize) >= 123))
  {
    ballSpeedX = -1 * fabs(ballSpeedX);
    collisionDeflection(player2Y);
  }
}

void collisionDeflection(double PY)
{
  double margin = 0.1;
  // Check if ball bounced on top of the paddle
  if ((ballY + ballSize - margin <= PY))
  {
    if (ballSpeedY > 0)
    {
      ballSpeedY -= 0.7;
    }
  }
  else if (((ballY + margin) >= (PY + 8)))
  {
    if (ballSpeedY < 0)
    {
      ballSpeedY += 0.7;
    }
  }
  else
  {
    collisionModifier(PY);
  }
}

void collisionModifier(double PY)
{
  double magnitude = ((PY - (ballSize / 2.0) + ((playerHeight + ballSize) / 2.0) - (ballY + (ballSize / 2.0))) / ((playerHeight + ballSize) / 2.0));
  double changeMax = 0.1;

  double modifier = (magnitude * changeMax);
  ballSpeedY += modifier;
}