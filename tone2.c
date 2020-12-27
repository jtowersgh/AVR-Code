#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRB |= 1 << PB4;		//Data Direction Register output for only
				//pin 3 on port B
    while (1)
    {
        PORTB ^= 1 << PB4;	//XOR (^) to toggle only pin 0 on Port B
        _delay_ms(1);		//Delay between the toggling on and off
    }
}
