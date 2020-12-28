/*
 * blinkSix.c
 *
 * Created: 2020-09-17 17:34
 * Author: Jeff
 */

#include <avr/io.h>

#define F_CPU 1000000UL
#include <util/delay.h>

#define BDLY 100

int main(void)
{
    DDRB	 = 0b00000111;		// Set PortB 0 thru 3
    PORTB	 = 0;			// Ensure all outputs off

    while(1)
    {
	// 1: 0 hi 1 lo 2 z
	DDRB  &= ~_BV(PORTB2);
	DDRB  |=  _BV(PORTB1);
	PORTB &= ~_BV(PORTB1);
	PORTB |=  _BV(PORTB0);
	_delay_ms(BDLY);

	// 2: 0 lo 1 hi 2 z
	PORTB &= ~_BV(PORTB0);
	PORTB |=  _BV(PORTB1);
	_delay_ms(BDLY);

	// 3: 0 z  1 hi 2 lo
	DDRB &= ~_BV(PORTB0);
	DDRB |=  _BV(PORTB2);
	PORTB &=~_BV(PORTB2);
	_delay_ms(BDLY);

	// 4: 0 z  1 lo 2 hi	 
	PORTB &= ~_BV(PORTB1);
	PORTB |=  _BV(PORTB2);
	_delay_ms(BDLY);

	// 5: 0 hi 1 z  2 lo
	DDRB &= ~_BV(PORTB1);
	DDRB |=  _BV(PORTB0);
	PORTB &=~_BV(PORTB2);
	PORTB |= _BV(PORTB0);
	_delay_ms(BDLY);

	// 6: 0 lo 1 z  2 hi
	PORTB &= ~_BV(PORTB0);
	PORTB |=  _BV(PORTB2);
	_delay_ms(BDLY);
    }
}
