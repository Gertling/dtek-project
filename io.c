#include <stdint.h>
#include <stdbool.h>
#include "header.h"
#include <pic32mx.h>

// volatile int * TRISB_egen = (volatile int *)0x86040;

volatile int *PORTBegen = (volatile int *)0xbf886050;

int getPlayerBtns(int btnNumber)
{
    switch (btnNumber)
    {
    case 1:
        if ((PORTB & 0x04) == 0) // Button 1 on breadboard. Port a0
        {
            return 1;
        }
        return 0;

        break;

    case 2:
        if ((PORTB & 0x010) == 0) // Button 2 on breadboard. Port a1
        {
            return 1;
        }
        return 0;

        break;

    case 3:

        if ((PORTB & 0x0100) == 0) // Button 3 on breadboard. Port a2
        {
            return 1;
        }
        return 0;
        break;

    case 4:

        if ((PORTB & 0x0400) == 0) // Button 4 on breadboard. Port a3
        {
            return 1;
        }
        return 0;

        break;

    default:
        return 0;
        break;
    }
}

int getbtns(void)
{
    int a = ((PORTD & 0x000000e0) >> 5);

    return (a);
}
