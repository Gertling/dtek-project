#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#include <math.h>

int getBase10Expo(int num)
{
    double temp = num;
    int log10Exp = 0;
    while (temp >= 10)
    {
        log10Exp++;
        temp /= 10;
    }
    return log10Exp;
}

void swap(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}

void reverse(char str[], int length) // stolen
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        swap(*(str + start), *(str + end));
        start++;
        end--;
    }
}

char *itoa(int num, char *str, int base) // Stolen
{
    int i = 0;

    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    // reverse(str, i);

    return str;
}