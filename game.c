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

double player1Y;
double player2Y;

double playerHeight;

int player1Score;
int player2Score;

bool getServeDelay()
{
  return serveDelay;
}

void setServeDelay(bool b)
{
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
  ballSpeedY = 0.2;
  ballSpeedX = 0.25;

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
  calculateBallImpact();
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
    player1Score++;
    onGoal(1);
  }
  if ((ballX + ballSize) > gameWidth - 1)
  {
    player2Score++;
    onGoal(2);
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
  calculateBallImpact();

  serveDelay = true;
  isPlaying = false;
  ballX = gameWidth / 2;  // Make ball start in middle
  ballY = gameHeight / 2; // Make ball start in middle

  ballSpeedY = 0.2;
  ballSpeedX = 0.25; // Give ball it's beginning direction and speed

  char word[16];

  int k;
  for (k = 0; k < 16; k++)
  {
    word[k] = ' ';
  }

  int exp = getBase10Expo(player2Score);
  char buffer[exp + 1];
  char *chars = itoa(player2Score, buffer, 10);

  int i;

  for (i = 0; i < exp + 1; i++)
  {
    word[6 - i] = chars[i];
  }

  // word[6] = chars[1];
  word[8] = ':';

  int exp2 = getBase10Expo(player1Score);
  char buffer2[exp2 + 1];
  char *chars2 = itoa(player1Score, buffer, 10);
  int j;

  for (j = 0; j < exp2 + 1; j++)
  {
    word[10 + exp2 - j] = chars[j];
  }

  display_string(0, word);
  display_update();
  display_image(0, goal, 128, 1, 3);
}

void paddleCollide()
{
  if (player1Y <= (ballY + ballSize) && ballY <= (player1Y + 8) && ballX <= 4)
  {
    ballSpeedX = fabs(ballSpeedX);
    collisionDeflection(player1Y);
    
    if (ai)
    {
      calculateBallImpact();
    }
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