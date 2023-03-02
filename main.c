/*
 * I2C Example project for the mcb32 toolchain
 * Demonstrates the temperature sensor and display of the Basic IO Shield
 * Make sure your Uno32-board has the correct jumper settings, as can be seen
 * in the rightmost part of this picture:
 * https://reference.digilentinc.com/_media/chipkit_uno32:jp6_jp8.png?w=300&tok=dcceb2
 */

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic32mx.h>
#include "header.h"

#define screen_width = 128;
#define screen_heigth = 32;

bool isTicked = false;

int mytime = 1;

int main(void)
{

	init();
	initGame();
	timer2();

	enablePixel(1, 1);
	// display_image(0, icon);

	TRISB = 0xffffffff;			// Sätter allt som finns till input :)
	TRISE = TRISE & 0xffffff00; // Egen TRISE, sätter till output
	/*int i;
	for(i = 0; i < 32; i++)
	{
		int j;
		for(j = 0; j < 128; j++)
		{
			enablePixel(j,i);
			display_image(0, icon);
			int k;
			for(k = 0; k < 100000; k++)
			{

			}
		}

	}*/
	// display_image(0, icon);

	while (1)
	{

		if (isTicked)
		{
			btnTimeoutCounter++;
			isTicked = false;
			switch (displayState)
			{
			case 0:
				mainMenu();
				break;
			case 1:
				leaderBoard();
				break;
			case 2:
				difficulty();
				break;
			case 3:
				game();
				break;
			case 4:
				gameMode();
				break;
			case 5:
				enterScore();
			default:
				break;
			}
		}

		//*porte_egen += 1;

		// delay(100);
	}

	return 0;
}

void replaceString(char *string1, char *string2, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		string1[i] = string2[i];
	}
}

void init(void) // This is all stolen.
{
	displayState = 0;
	btnTimeoutCounter = 0;
	aiDiff = 0;
	ai = false;
	replaceString(name1, "AAA", 3);
	replaceString(name2, "AAB", 3);
	replaceString(name3, "AAC", 3);


	highscore1 = 0;
	highscore2 = 0;
	highscore3 = 0;

	SYSKEY = 0xAA996655; /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA; /* Unlock OSCCON, step 2 */
	while (OSCCON & (1 << 21))
		;				  /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while (OSCCON & (1 << 21))
		;		  /* Wait until PBDIV ready */
	SYSKEY = 0x0; /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
	SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
	display_init();
	/*
	display_string(0, "KTH/ICT lab");
	display_string(1, "in Computer");
	display_string(2, "Engineering");
	display_string(3, "      Welcome!");
	*/
	display_update();
}