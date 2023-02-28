#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic32mx.h>
#include "header.h"

// stolen from lab, written by us
void timer2(void)
{
    T2CON = 0x70; // Pre-scale
    /*T2CON |= 0xC000;
    T2CON |= 0x4;*/
    TMR2 = 0;

    IEC(0) = (1 << 8);
    IPC(2) = 4;

    enable_interrupt(); // enable_interrupt from labwork.S

    PR2 = 1250;      // 625;     // Sätter delayen korrekt (3125 * 256 = 800 000) Räknar med pre-scale
    T2CON |= 0x8000; // Starts the timer
}

int serveDelayCount = 0;

void user_isr(void)
{

    // IFSCLR(0);

    if (IFS(0) & 0x100) // If flag of timer 2 raised, reset flag. assignment 3e.
    {
        isTicked = true;
        IFSCLR(0) = 0x100; // Code to reset flag. The sooner the better. Source: Trust me bro.

        if (getServeDelay())
        {
            serveDelayCount++;
            if (serveDelayCount >= 500)
            {
                setServeDelay(false);
                startGame();
                serveDelayCount = 0;
            }
        }

        // IFS(0) = IFS(0) & 0x00000800;
    }
    // IFS(0) = 0; // Since there could be other flags raised.
    return;
}