/*
 * externalInterrupts.c
 *
 * Created: 9/5/2020 21:01
 * Author: Jeff
 */

#define F_CPU 1E6

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int cliflag =	0;

int main(void)
{
    DDRB = 	(1 << PORTB0);	//set LED pin as output
    PORTB = 	(1 << PORTB0);	//set LED on at begginning

    PORTB =	(1 << PORTB2);	//set pull-up on interrupt pin
    GIMSK =	(1 << INT0);	//enable external interrupt on INT0 pin

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

ISR(INT0_vect)
{
    PORTB ^=	(1 << PORTB0);
    cliflag = 1;
}
