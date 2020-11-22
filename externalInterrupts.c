/*
 * externalInterrupts.c
 *
 * Created: 9/5/2020 21:01
 * Author: Jeff
 */

#define F_CPU 16E6

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int cliflag =	0;

int main(void)
{
    DDRB = 	(1 << PORTB0);
    PORTB = 	(1 << PORTB0);

    PORTD =	(1 << PORTD3);
    EIMSK =	(1 << INT1);

    while(1)
    {
	if (cliflag == 0)
	{
	    sei();
	}
	else
	{
	    cli();
	    _delay_ms(2000);
	    cliflag = 0;
	}
    }
}

ISR(INT1_vect)
{
    PORTB ^=	(1 << PORTB0);
    cliflag = 1;
}
