/*
 * _8bitTimer.c
 * To calculate for AVR Timer:
 * https://eleccelerator.com/avr-timer-calculator/
 * Author: Jeff
 */

#include <avr/io.h>
#include <avr/interrupt.h>

int extraTime = 0;

int main(void)
{
    DDRB = (1 << PB0);		//Set PortB 0 to output LED
    TCCR0A = (1 << WGM01);	//Set CTC Bit
    TCCR0B = (1 << CS01);	//Set prescaler to divide by 8
    OCR0A = 250;
    TIMSK = (1 << OCIE0A);
    sei();

    while(1)
    {
	//TODO:: Application code
    }
}

ISR(TIMER0_COMPA_vect)
{
    extraTime++;

    if(extraTime > 500)
    {
	PORTB ^= (1 << PB0);
	extraTime = 0;
    }
}
