/*
 * fastpwm.c
 *
 * Created: 2020-10-01 18:45
 * Author: Jeff
 *
 * Modified: 2020-10-05 21:54
 * Fix incorrectly set Output Compare Registers in Timer1. (Exceeded 8 bit
 * register.)
 */

#include <avr/io.h>

#define F_CPU 1000000UL
#include <avr/interrupt.h>

// This is the number of 1ms delays to give a slowly changing PWM.
#define PWM_COUNTING_TIME 50

// This variable counts the number of 1ms delays.
uint8_t pwmCount = PWM_COUNTING_TIME;

/* A flag is set every time Timer 1 times out (1ms). Make it volatile so
 * the compiler won't optimize it out and it will be visible in the main()
 * function. */
volatile uint8_t timer1Flag;

/* This is the Timer 1 Compare A interrupt service routine. Runs every 1ms
 * when the timer times out. All it does is sets a flag.
 * - Important to keep it simple! */
ISR(TIMER1_COMPA_vect)
{
    timer1Flag = 1;
}

int main(void)
{
    /* Set up the IO port registers for the IO pins connected to the PWM
     * output pin OC0A (PB0) and OC0B (PB1). */
    DDRB |= (_BV(PB0)    | _BV(PB1));
    PORTB &= (~_BV(PB0)   & ~_BV(PB1));

    /* Set up Timer 1 to generate a 1ms interrupt:
     - clocked by F_CPU / 8
     - CTC on OCR1C
     - generate interrupt when OCR1A matches TCNT1
     - load OCR1C with the delay count to get 1ms delay
    */

    // Set Timer 1 to CTC mode and clock div by 8 (125000 ticks per second)
    TCCR1  |= (_BV(CTC1)    | _BV(CS12));
    // Set output compare register C for CTC (upper limit) for 1ms
    // Set output compare register A for output compare flag
    OCR1C   = ((F_CPU / 8 / 1000) -1);   /* 124 */
    OCR1A   = OCR1C;
    TIMSK   = _BV(OCIE1A); /* enable match A interrupt */

    /* Set up Timer 0 to generate a Fast PWM signal:
     * - clocked by F_CPU, no prescale
     * - non-inverted output
     */
    // Set to FastPWM and clear OCOA/B on Compare Match
    TCCR0A = (_BV(WGM00) | _BV(WGM01) | _BV(COM0A1) | _BV(COM0B1));
    TCCR0B = _BV(CS00); /* Set no prescaler */
    OCR0A  = 0; /* start with duty cycle = 0% */
    OCR0B  = 255; /* start with duty cycle = 100% */

    /* enable the interrupt system */
    sei();

    /* run around this loop foever */
    while (1)
    {
        if(timer1Flag == 1) /* test the 1ms flag. Is it set? */
        {
            timer1Flag = 0; /* reset the flag */

            if(--pwmCount == 0)
            {
                pwmCount = PWM_COUNTING_TIME;
                ++OCR0A;
                --OCR0B;

            }
        }
    }
}
