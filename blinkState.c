/*
 * blinkState.c
 *
 * Created: 2020-09-20 17:51
 * Author: Jeff
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#define LED_BLINK_TIME 50	//define blink delay

enum
{
    ledState0,
    ledState1,
    ledState2,
    ledState3,
    ledState4,
    ledState5,
    maxLedState
};

volatile uint8_t ledState = 0;
volatile uint8_t ovCount = 0;
uint8_t ledDelay = LED_BLINK_TIME;

ISR(TIMER0_COMPA_vect)
{
   ovCount++;

   if(ovCount > ledDelay)
   {
	ledState++;
	ovCount = 0;
   }
}

int main(void)
{
    DDRB   = 0b00000111;	// Set PortB 0 thru 2
    PORTB  = 0;			// Ensure all outputs off

    TCCR0A = 0b00000010;	// Set WGM0 and WGM1 for CTC mode
    TCCR0B = 0b00000101;	// Set WGM2. Set CS to /1024 prescalr
    OCR0A  = 155;		// F_CPU / 1024 / 100 - 1
    TIMSK0 = 0b00000010;	// Output compare Match interrupt enable

    sei();

    while(1)
    {
    switch(ledState)
	{
	    case ledState0:
		// 1: 0 hi 1 lo 2 z
		DDRB  &= ~_BV(PORTB2);
		DDRB  |=  _BV(PORTB1);
		PORTB &= ~_BV(PORTB1);
		PORTB |=  _BV(PORTB0);
		break;

	    case ledState1:
		// 2: 0 lo 1 hi 2 z
		PORTB &= ~_BV(PORTB0);
		PORTB |=  _BV(PORTB1);
		break;

	    case ledState2:
		// 3: 0 z  1 hi 2 lo
		DDRB &= ~_BV(PORTB0);
		DDRB |=  _BV(PORTB2);
		PORTB &=~_BV(PORTB2);
		break;

	    case ledState3:
		// 4: 0 z  1 lo 2 hi	 
		PORTB &= ~_BV(PORTB1);
		PORTB |=  _BV(PORTB2);
		break;

	    case ledState4:
		// 5: 0 hi 1 z  2 lo
		DDRB &= ~_BV(PORTB1);
		DDRB |=  _BV(PORTB0);
		PORTB &=~_BV(PORTB2);
		PORTB |= _BV(PORTB0);
		break;

	    case ledState5:
		// 6: 0 lo 1 z  2 hi
		PORTB &= ~_BV(PORTB0);
		PORTB |=  _BV(PORTB2);
		break;

	    case maxLedState:
		ledState = 0;
		break;

	    default:
		break;

	}/* end switch statement */
    }/* end of while statement */
}/* end of main */
