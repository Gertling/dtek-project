/*
 * I2C Example project for the mcb32 toolchain
 * Demonstrates the temperature sensor and display of the Basic IO Shield
 * Make sure your Uno32-board has the correct jumper settings, as can be seen
 * in the rightmost part of this picture:
 * https://reference.digilentinc.com/_media/chipkit_uno32:jp6_jp8.png?w=300&tok=dcceb2
 */

//#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "header.h"


int main(void) {

	while (1)
	{
		//delay(100);
		tickGame();
	}
	
	
	
	return 0;
}

