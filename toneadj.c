/*
 * sqWave.c
 *
 * Created: 2020-12-06 1707
 * Author: Jeff
 *
 * Creates a square wave. Intended to be development for a squarewave
 * library.
 *
 * Attiny85 fuse clock divider by 8 should be turned off. (8Mhz clock)
 * Timer0 is responsible for generating the sine tone. Resolution
 * is acheived by using the full 8MHz clock, and using CTC mode to create
 * numerous compare match interrupt vectors. The interrupts will be counted
 * using isr() to count matches and increment variable "periodIncrement". When
 * periodIncrement reaches "periodMatchCount", the output pin is toggled. 
 * Variable
 * "periodMatchCount" will be adjusted to change tone frequency.
 * Using Timer0 in CTC mode such that it clears after 0.0000025 seconds.
 * 1 / 8000000  * 20 = 0.0000025
 * OCR0A = 19
 *
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "sqWave.h"
#define F_CPU 8000000
#include <math.h>

uint16_t periodIncrement = 0; 
volatile uint16_t period = 40000;
double octaves = 0;
double mult = 2;

void initializeSqWave(void)
{
    TCCR0A = 1<<WGM01;  // Set WGM01 for CTC mode
    OCR0A = 19;        // Set TOP match for 19 to set each count for
    TIMSK = 1<<OCIE0A;   // Set OCIE0A for compare match interrupt enable
    
    sei();

}

ISR(TIMER0_COMPA_vect)
{
    periodIncrement++;    

    if(periodIncrement > period)
    {
        PORTB ^= 1<<PB4;
        periodIncrement = 0;    
    }
}

ISR(ADC_vect)
{

    ADCSRA |= 1<<ADSC;
}
void startSqWave(void)
{
    TCCR0B = 1<<CS00;   // Set clock with no prescaler
}

void stopSqWave(void)
{
    TCCR0B &= ~(1<<CS00);   // clear clock
}

void setOutputPortB(uint8_t outPin)
{
    DDRB = 1<<outPin;   // Set IO pin for output
    PORTB = 0;          // Ensure all outputs off
}

/*void runSqWave(uint16_t periodMatchCount, uint8_t outPin)
{    
    if(periodIncrement > periodMatchCount)
    {
        PORTB ^= 1<< outPin;
        periodIncrement = 0;
    }
}*/

int main(void)
{

    ADMUX |= 1<<MUX1 | 1<<MUX0;
    ADCSRA |= 1<<ADIE;
    ADMUX |= 1<<ADLAR;
    ADCSRA |= 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;
    ADCSRA |= 1<<ADEN;
    sei();
    ADCSRA |= 1<<ADSC;

    initializeSqWave();
    setOutputPortB(4);
    startSqWave();

    while(1)
    {
        
    octaves = 0.0339 * ADCH;
    period = 40000 / (pow( mult , octaves));
    }
}
