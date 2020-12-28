/*
 * rxSerial.c
 * 
 * Author: Jeff
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

#define F_CPU	16000000
#define BAUD	9600
#define BRC	((F_CPU/16/BAUD)-1)

#include <util/delay.h>
#define RX_BUFFER_SIZE 128

char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

char getChar(void);
char peekChar(void);

int main(void)
{
    // UBRR0 is the Baud Rate register and is split into
    // an upper 4 bit nibble and lower 8 bit register.

    UBRR0H =	(BRC >> 8);			//Upper 8 bits of BRC
    UBRR0L =	 BRC;				//Lower 8 bits of BRC

    UCSR0B = (1 << RXEN0)  | (1 << RXCIE0);	//Enable RX and Interrupt
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    DDRB = (1 << PORTB0);			//PortB0 as output

    sei();

    while(1)
    {
	char c = getChar();

	if(c == '1')
	{
	    sbi(PORTB, PORTB0);
	}	
	else if(c =='0')
	{
	    cbi(PORTB, PORTB0);
	}
    }

}

char peekChar(void)
{
    char ret = '\0';

    if(rxReadPos != rxWritePos)
    {
	ret = rxBuffer[rxReadPos];
    }

    return ret;
}

char getChar(void)
{
    char ret = '\0';

    if(rxReadPos != rxWritePos)
    {
	ret = rxBuffer[rxReadPos];

	rxReadPos++;

	if(rxReadPos >= RX_BUFFER_SIZE)
	{
	    rxReadPos = 0;
	}
    }
    return ret;
}

ISR(USART_RX_vect)
{
    rxBuffer[rxWritePos] = UDR0;

    rxWritePos++;

    if(rxWritePos >= RX_BUFFER_SIZE)
    {
	rxWritePos = 0;
    }
}
