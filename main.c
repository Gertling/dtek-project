/*
 * I2C Example project for the mcb32 toolchain
 * Demonstrates the temperature sensor and display of the Basic IO Shield
 * Make sure your Uno32-board has the correct jumper settings, as can be seen
 * in the rightmost part of this picture:
 * https://reference.digilentinc.com/_media/chipkit_uno32:jp6_jp8.png?w=300&tok=dcceb2
 */

// #include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "header.h"
volatile int *trise_egen = (volatile int *)0xbf886100;
volatile int *porte_egen = (volatile int *)0xbf886110;

volatile int *TRISB_egen = (volatile int *)0xbf886040;
volatile int *PORTBegen1 = (volatile int *)0xbf886050;

int mytime = 1;
int main(void)
{

	*TRISB_egen = 0xffffffff; // Sätter allt som finns till input :) 
	*trise_egen = *trise_egen & 0xffffff00; // Egen TRISE, sätter till output

	while (1)
	{

		*porte_egen = (*PORTBegen1 & 0xff);

		if (getPlayerBtns(1))
		{
			
		}

		//*porte_egen += 1;

		int i;
		for (i = 0; i < 1000000; i++)
		{
			/* code */
		}

		// delay(100);
	}

	return 0;
}
