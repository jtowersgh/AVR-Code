#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRB |= 1 << PINB5;		//Data Direction Register output for only
				//pin 5 on port B
    while (1)
    {
        PORTB ^= 1 << PINB5;	//XOR (^) to toggle only pin 5 on Port B
        _delay_ms(100);		//Delay between the toggling on and off
    }
}
