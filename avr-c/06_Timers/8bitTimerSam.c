/*
 * _8bitTimer.c
 *
 *  Author: SAM
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

int extraTime = 0;

int main(void)
{
	DDRB = 0x01;
	
	TCCR0A = (1 << WGM01); //Set CTC Bit
	OCR0A = 195;
	TIMSK0 = (1 << OCIE0A);
	
	sei();
	
	TCCR0B = (1 << CS02) | (1 << CS00); //start at 1024 prescalar
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}
