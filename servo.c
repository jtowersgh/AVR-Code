/*
 * servo.c
 *
 * Created: 2020-10-18
 * Author : Jeff Towers
 *
 * Source code for experimenting with small servo Tower Pro Micro Servo
 * 9g SG90.
 *
 * This program uses the struct, union and typedef code for an alternate way of
 * accessing the control registers of Timer 1 and Timer 2.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 3
 * or the GNU Lesser General Public License version 3, both as
 * published by the Free Software Foundation.
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "m328p_tc1.h"
#include "m328p_tc2.h"

// This is the number of 1ms delays to give us a slowly changing PWM. 
#define PWM_CHANGE_TIME 100

/* This variable counts the number of 1ms delays. */
uint8_t pwmCount = PWM_CHANGE_TIME;
//uint8_t my_ocr1a = F_CPU / 8 / 1000 - 1;
//uint16_t my_icr1 = F_CPU / 8 / 50 -1;


/* A flag that is set every time Timer 2 times out (1ms).  Make it volatile
 * so the compiler won't optimize it out and it will be visible in the main()
 * function. */
volatile uint8_t timer2Flag;

/* These are temporary data structures to hold the information for programming
   Timer 1 and Timer 2. */
Timer_Counter1 timer1;
Timer_Counter2 timer2;

/* This is the Timer 2 Compare A interrupt service routine.  Runs every 1ms
   when the timer times out.  All it does is sets a flag.
   - Important to keep it short and simple! */
ISR(TIMER2_COMPA_vect)
{
  timer2Flag = 1;
}

/* This is where it all happens. */
int main(void)
{
  /* Set up the IO port registers for the IO pin connected to the PWM output
   * pin OC1A (PB1)*/
  DDRB |= _BV(PORTB1);
  PORTB &= ~_BV(PORTB1);

  /* Set up Timer 2 to generate a 1ms interrupt:
     - clocked by F_CPU / 1024
     - generate interrupt when OCR2A matches TCNT2
     - load OCR2A with the delay count to get 1ms delay
   */
  tc2_get_config(timer2);
  timer2.tccr2a.wgm2l = TC2_TCCR2A_M2_CTC; /* TC2 Mode 2, Clear timer on match */
  timer2.tccr2a.com2a = TC2_TCCR2A_OC2A_MODE0; /* OC2A pin disabled */
  timer2.tccr2a.com2b = TC2_TCCR2A_OC2B_MODE0; /* OC2B pin disabled */
  timer2.tccr2b.cs2 = TC2_TCCR2B_CLK_PRSC128; /* TC0 clocked by F_CPU/128 */
  timer2.tccr2b.wgm2h = 0; /* upper bit of TC0 Mode */
  timer2.ocr2a = (F_CPU / 128 / 1000 - 1); /* (clock cycles prescaled per
                                              second / required timer resets
                                              per second) = 124 */
  timer2.timsk2.ocie2a = 1; /* enable OCIE2A, match A interrupt */
  tc2_set_config(timer2);

  /* Set up Timer 1 to generate a Fast PWM signal:
     - clocked by F_CPU (fastest PWM frequency)
     - non-inverted output
   */
  tc1_get_config(timer1);
  timer1.tccr1a.wgm1l = TC1_TCCR1A_MODE14; /* TC1 Mode 14, Fast PWM with TOP
                                            * at ICR1 */
  timer1.tccr1b.wgm1h = TC1_TCCR1B_MODE14; /* TC1 Mode 14, Fast PWM with TOP
                                            * at ICR1 */
  timer1.tccr1a.com1a = TC1_TCCR1A_OC1A_MODE2; /* clear OC1A on match */
  timer1.tccr1a.com1b = TC1_TCCR1A_OC1B_MODE0; /* OC1B pin disabled */
  timer1.tccr1b.cs1 = TC1_TCCR1B_CLK_PRSC8; /* TC1 F_CPU divided by 8 */
//  timer1.ocr1a = 1999; /* start with 1ms pulse 
//                                                   (0º angle) */
  OCR1A = 1999;                                                   
//  timer1.icr1.icr1_reg = 39999; /* set PWM for 20ms period (50 
//                                              cycles per second. */
  ICR1 = 39999;
  tc1_set_config(timer1);
//  tc1_set_ocr1a(1999);
  /* enable the interrupt system */
  sei();

  /* run around this loop for ever */
  while (1) 
  {
/*      
    if(timer2Flag == 1)  test the 1ms flag, is it set?  
    {
      timer2Flag = 0;  reset the 1ms flag  

      if(--pwmCount == 0)  decrement and test the delay timer 
      {
        pwmCount = PWM_CHANGE_TIME;  reset the delay timer  
        if(OCR1A < (F_CPU / 8 / 500 - 1))
        {
            ++OCR1A;  change the duty cycle  
        }
        else OCR1A = (F_CPU / 8 / 1000 - 1);

      }

    }
*/
  }
}
