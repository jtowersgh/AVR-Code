#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


int main()
{
    char string[9];
    int clearBV = 0;
    int setBV = 0;
    int DDRB = 0b01000000;

    printf("Enter 8 character string: \n");
    scanf("%s",string);


    for (int i = 0; i < 8; i++)
    {
	clearBV += (pow(2,i) *(string[7-i] != '0'));
	setBV   += (pow(2,i) *(string[7-i] == '1'));
    }

    printf("clearBV = %d\n", clearBV);
    printf("setBV   = %d\n", setBV);
    DDRB &= clearBV;
    DDRB |= setBV;
    printf("%d\n", DDRB);
    exit(0);
}
