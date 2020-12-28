#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRB |= 1 << PB0;		//Data Direction Register output for only
				//pin 0 on port B
    DDRB &= ~(1 << PB1);	//Data Direction Register input for 
				//pin 1 on port B
    PORTB |= 1 << PB1;		//set pull-up resistor on PB1

    while (1)
    {
        if(!(PINB & (1 << PB1))) //When button is pressed
        {
            PORTB |= 1 << PB0;   //Turn on LED
	}

	else
	{
	    PORTB &= ~(1 << PB0);//Torn off LED
	}
    }
}
