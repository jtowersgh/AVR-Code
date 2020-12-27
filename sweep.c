/*
 * sweep.c
 *
 * Created: 2020-11-30 2031
 * Author: Jeff
 *
 * Simulates a 5Hz to 2000Hz square sweep using a passive piezo buzzer
 *
 * Attiny85 fuse clock divider by 8 should be turned off. (8Mhz clock)
 * Timer0 is responsible for generating the sine tone. Resolution
 * is acheived by using the full 8MHz clock, and using CTC mode to create
 * numerous compare match interrupt vectors. The interrupts will be counted
 * using isr() to count matches and increment variable "periodIncrement". When
 * periodIncrement reaches "piezoToggle", the output pin is toggled. Variable
 * "piezoToggle" will be adjusted to change tone frequency.
 * Using Timer0 in CTC mode such that it clears after 0.0000025 seconds.
 * 1 / 8000000  * 20 = 0.0000025
 * OCR0A = 19
 *
 * Using Timer1 in CTC mode. Timer1 has extensive prescaler options.
 * Clk divided by 2048 will be used as it divides the counts evenly into
 * one minute.
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

uint32_t elapsedCount = 0;
<<<<<<< HEAD
volatile uint16_t periodIncrement = 0; 
=======
volatile uint8_t periodIncrement = 0; 
>>>>>>> 80c719a59f215dc555948a2d3faf2bb8db564cfc
uint8_t sweepCount = 0;
volatile int elapseFlag = 0;
uint16_t periodMatchCount = 40000;

ISR(TIMER0_COMPA_vect)
{
    periodIncrement++;    
}

ISR(TIMER1_OVF_vect)
{
    elapseFlag = 1;
}

int main(void)
{
    DDRB = 1<<PORTB3;   // Set IO Pin 3 to output
    PORTB = 0;          // Ensure all outputs off

    TCCR0A = 1<<WGM01;  // Set WGM01 for CTC mode
    TCCR0B = 1<<CS00;   // Set clock with no prescaler
    OCR0A = 19;        // Set TOP match for 19 to set each count for
    TIMSK = 1<<OCIE0A;  // Set OCIE0A for compare match interrupt enable

    TCCR1 = 1<<CS12;    // Set Timer/counter 1 clock prescaler to 8
    TIMSK = 1<<TOIE1;   // Set overflow interrupt enable timer1

    sei();

    while(1)
    {
        if(elapseFlag == 1)
        {
            elapseFlag = 0;
            if(sweepCount == 0)
            {
                elapsedCount++;
            }
            else if(sweepCount == 1)
            {
                elapsedCount--;
            }
            else
            {
                TCCR0B &= ~(1<<CS00);
            }
        }
        
<<<<<<< HEAD
        if(periodIncrement > 57)
=======
        if(periodIncrement > periodMatchCount)
>>>>>>> 80c719a59f215dc555948a2d3faf2bb8db564cfc
        {
            PORTB ^= 1<< PINB3;
            periodIncrement = 0;
        }

        periodMatchCount = 40000 / pow(2.0, elapsedCount/234375);

        if(periodMatchCount < 100)
        {
            sweepCount++;
        }
            else if(periodIncrement > 40000)
            {
                sweepCount++;
            }
    }
}
