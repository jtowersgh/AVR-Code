/*
 * _l6bitTimer.c
 *
 *
 * Author: Jeff
 */

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRB = (1 << PB5);		//Set PortB 5 to output LED
    TCCR1A = (1 << WGM12);	//Set CTC Bit
    TCCR1B = (1 << CS12);	//Set prescaler to divide by 256
    OCR1A = 6250;
    TIMSK1 = (1 << OCIE1A);
    sei();

    while(1)
    {
	//TODO:: Application code
    }
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PB5);
}
