#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "header.h"

int alterPixel(int x, int y)
{
  int section = floor(y / 128);

  int row = y - (section * 128);
  int column = x;

  int index = section * 128 + column;

  printf("before: %d", logo[index]);

  logo[index] |= pow(2, row);

  return logo[index];
}

int main()
{
  printf("output: %d", alterPixel(5, 128));

  return 0;
}