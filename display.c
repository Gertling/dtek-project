#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "header.h"

void clearIcon(){
  int i;

  for ( i = 0; i < 512; i++)
  {
    icon[i] = 0;
  }
  
 
}

void enablePixel(int x, int y)
{
  if(x > 127){
    x = 127;
  }
  int section = floor(y / 8); // Find section (0, 1, 2, 3)

  int row = y - (section * 8); // Each section now has 8 rows.
  int column = x;
  

  int index = section * 128 + column; // Index x-led


  icon[index] |= myPow(2, row); // The byte in the section we want to change

}


int myPow(int base, int exp)
{
  int count = 1;
  int i;
  for ( i = 0; i < exp; i++)
  {
    count *= base;
  }

  return count;

}
