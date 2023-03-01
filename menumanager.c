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

void leaderBoard()
{
    // 4 highest scores
    int scores[3];
    display_string(0, "Leaderboard:");
    display_string(1, "score1");
    display_string(2, "score2");
    display_string(3, "score3");
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
        }
        if (getbtns() & 0x2)
        {
            aiDiff = 1;
            btnTimeoutCounter = 0;
        }
        if (getbtns() & 0x4)
        {
            aiDiff = 0;
            btnTimeoutCounter = 0;
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

    if (count >= 5) // So that we only display the game every 10 ticks.
    {
        count = 0;
        displayGame();
    }
    count++;
}

void displayGame()
{
    if (!getServeDelay())
    {
        displayPlayer(1, getPlayerPosition(1));

        displayPlayer(2, getPlayerPosition(2));

        displayBall(getBallPositionX(), getBallPositionY());
        //PORTE = (getBallPositionY()); // Lyser fint
        display_image(0, icon, 128, 0, 3);

        clearIcon();
    }
}