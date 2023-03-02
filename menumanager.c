#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#include <math.h>
#include <pic32mx.h>

int count = 0;

void mainMenu()
{

    display_string(0, "Play");
    display_string(1, "Difficulty");
    display_string(2, "Leaderboard");
    display_string(3, "");
    display_update();

    if (btnTimeoutCounter > 100)
    {
        if (getbtns() & 0x1)
        {
            displayState = 1; // Leaderboard
            btnTimeoutCounter = 0;
        }
        if (getbtns() & 0x2)
        {
            displayState = 2; // Difficulty
            btnTimeoutCounter = 0;
        }
        if (getbtns() & 0x4)
        {
            displayState = 4; // Game/play -> gameMode select
            btnTimeoutCounter = 0;
        }
    }
}
void gameMode()
{
    display_string(0, "Singelplayer");
    display_string(1, "Multiplayer");
    display_string(2, "");
    display_string(3, "");
    display_update();

    if (btnTimeoutCounter > 100)
    {
        if (getbtns() & 0x1)
        {
            // Back button
            displayState = 0;
            btnTimeoutCounter = 0;
        }
        if (getbtns() & 0x2)
        {
            ai = false;
            initGame();
            startGame();
            displayState = 3;
            btnTimeoutCounter = 0;
        }
        if (getbtns() & 0x4)
        {
            ai = true;
            initGame();
            startGame();
            displayState = 3;
            btnTimeoutCounter = 0;
        }
    }
}

char *lbString(char *name, int score)
{
    int exp = getBase10Expo(score);
    char buffer[exp + 1];
    char *chars = itoa(score, buffer, 10);

    char string[16];

    int i;
    for (i = 0; i < 3; i++)
    {
        string[i] = name[i];
    }

    string[3] = 0x20;

    int j;
    int k = 0;
    for (j = 0; j < exp + 1; j++)
    {
        string[4 + k++] = chars[exp - j];
    }

    string[exp + 4 + 1] = 0;

    return string;
}

void leaderBoard()
{
    // 4 highest scores
    int scores[3];
    display_string(0, "Leaderboard:");

    display_string(1, lbString(name1, highscore1));
    display_string(2, lbString(name2, highscore2));
    display_string(3, lbString(name3, highscore3));
    display_update();

    if (btnTimeoutCounter > 100)
    {
        // All buttons bring us back to main menu.
        if (getbtns() & 0x1)
        {
            // Back button
            displayState = 0;
            btnTimeoutCounter = 0;
        }
        if (getbtns() & 0x2)
        {

            displayState = 0;
            btnTimeoutCounter = 0;
        }
        if (getbtns() & 0x4)
        {
            displayState = 0;
            btnTimeoutCounter = 0;
        }
    }
}

void difficulty()
{
    display_string(0, "Easy");
    display_string(1, "Medium");
    display_string(2, "Hard");
    display_string(3, "");
    display_update();

    if (btnTimeoutCounter > 100)
    {
        if (getbtns() & 0x1)
        {
            aiDiff = 2;
            btnTimeoutCounter = 0;
            displayState = 0;
        }
        if (getbtns() & 0x2)
        {
            aiDiff = 1;
            btnTimeoutCounter = 0;
            displayState = 0;
        }
        if (getbtns() & 0x4)
        {
            aiDiff = 0;
            btnTimeoutCounter = 0;
            displayState = 0;
        }
    }
}

void game()
{

    // Måste då gamemode callas här direkt?
    if (ai == false)
    {
        if (getPlayerBtns(1))
        {
            updatePlayerPos(-0.2, 1);
        }
        if (getPlayerBtns(2))
        {
            updatePlayerPos(0.2, 1);
        }
        if (getPlayerBtns(3))
        {
            updatePlayerPos(-0.2, 2);
        }
        if (getPlayerBtns(4))
        {
            updatePlayerPos(0.2, 2);
        }
    }
    else
    {
        if (getPlayerBtns(1)) // Player
        {
            updatePlayerPos(-0.2, 1);
        }
        if (getPlayerBtns(2)) // Player
        {
            updatePlayerPos(0.2, 1);
        }

        aiHandler(); // "ai"
    }

    tickGame();

    if (count >= 5) // So that we only display the game every 5 ticks.
    {
        count = 0;
        displayGame();
    }
    count++;
    if (btnTimeoutCounter > 100)
    {
        if (getbtns())
        {
            displayState = 5;
            btnTimeoutCounter = 0;
        }
    }
}

void displayGame()
{
    if (!getServeDelay())
    {
        displayPlayer(1, getPlayerPosition(1));

        displayPlayer(2, getPlayerPosition(2));

        displayBall(getBallPositionX(), getBallPositionY());
        // PORTE = (getBallPositionY()); // Lyser fint
        display_image(0, icon, 128, 0, 3);

        clearIcon();
    }
}

void swap2(char *x, char *y, int length)
{
    char temp[length];
    replaceString(temp, x, length);

    replaceString(x, y, length);
    replaceString(y, temp, length);
}

void swap3(int *int1, int *int2)
{
    int temp = *int1;
    *int1 = *int2;
    *int2 = temp;
}

void enterScore()
{
    int playerScore;
    if (ai)
    {
        // Only check player1 since ai cant get highscore
        playerScore = player1Score;
    }
    else
    {
        playerScore = player1Score > player2Score ? player1Score : player2Score;
    }

    player1Score = 0;
    player2Score = 0;

    if (playerScore <= highscore3)
    {
        displayState = 1;
        return;
    }

    getName();

    if (playerScore > highscore1)
    {
        swap2(name1, name2, 3);
        swap3(&highscore1, &highscore2);

        swap2(name1, name3, 3);
        swap3(&highscore1, &highscore3);

        highscore1 = playerScore;
        replaceString(name1, currentName, 3);
    }
    else if (playerScore > highscore2)
    {
        swap2(name2, name3, 3);
        swap3(&highscore2, &highscore3);

        highscore2 = playerScore;
        replaceString(name2, currentName, 3);
    }
    else if (playerScore > highscore3)
    {
        highscore3 = playerScore;
        replaceString(name3, currentName, 3);
    }
    displayState = 1;
}

char currentLetter = 0x20;
int counter = 0;

char name[3] = "   ";
int delayCounter2 = 0;
void getName()
{
    currentLetter = 0x20;
    counter = 0;
    replaceString(name, "   ", 3);
    nameDisplayUpdate();
    while (counter < 3)
    {
        if (delayCounter2 >= 50)
        {

            if (getbtns() & 0x1)
            {
                if (currentLetter == 0x20)
                {
                    currentLetter = 0x41;
                }
                else if (currentLetter == 0x5a)
                {
                    currentLetter = 0x20;
                }
                else
                {
                    currentLetter++;
                }
                delayCounter2 = 0;
                nameDisplayUpdate();
            }
            if (getbtns() & 0x2)
            {
                name[counter++] = currentLetter;
                currentLetter = 0x20;
                delayCounter2 = 0;
                nameDisplayUpdate();
            }
            if (getbtns() & 0x4)
            {
                if (currentLetter == 0x20)
                {
                    currentLetter = 0x5a;
                }
                else if (currentLetter == 0x41)
                {
                    currentLetter = 0x20;
                }
                else
                {
                    currentLetter--;
                }
                delayCounter2 = 0;
                nameDisplayUpdate();
            }
        }
        else
        {
            delayCounter2++;
        }

        delay(10);
    }
    name[3] = 0;
    replaceString(currentName, name, 3);
}

void nameDisplayUpdate()
{
    display_string(0, "> leaderboard <");
    char x[1];
    x[0] = currentLetter;
    display_string(1, x);
    char string[16] = "Name:           ";
    string[6] = name[0];
    string[7] = name[1];
    string[8] = name[2];
    display_string(2, string);
    display_string(3, "");
    display_update();
}
