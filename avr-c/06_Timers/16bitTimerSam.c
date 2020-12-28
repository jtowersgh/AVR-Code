/*
 * _16bitTimer.c
 *
 * Created: 12/20/2012 3:18:46 PM
 *  Author: SAM
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB = 0x01;
	
	TCCR1B = (1 << WGM12);
	OCR1A = 19531;
	TIMSK1 = (1 << OCIE1A);
	
	sei();
	
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PORTB0);
}
