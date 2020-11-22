/*
 * txSerial.c
 * 
 * Author: Jeff
 */

#include <avr/io.h>

#define F_CPU	16000000
#define BAUD	9600
#define BRC	((F_CPU/16/BAUD)-1)
#define TX_BUFFER_SIZE 128

#include <util/delay.h>

int main(void)
{
    // UBRR0 is the Baud Rate register and is split into
    // an upper 4 bit nibble and lower 8 bit register.

    UBRR0H =	(BRC >> 8);	//Upper 8 bits of BRC
    UBRR0L =	 BRC;		//Lower 8 bits of BRC

    UCSR0B =	(1 << TXEN0);  	//Enable transmitter
    UCSR0C =	(1 << UCSZ01) | (1 << UCSZ00);	//8 bit data frame

    while(1)
    {
	UDR0 =	'8';
	_delay_ms(1000);
    }
}
