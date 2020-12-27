/*
 * ADCexample.c
 *
 * Created: 8/12/2020 15:27
 * Author: Jeff
 */

#include <avr/io.h>
#include <avr/interrupt.h>
int main(void)
{

    //Configure the ADC
    //Use Vcc as Voltage Reference (REFS0 REFS1 unset)

    //Set ADC3 (PB3) as single-ended ADC input
    ADMUX |= 1<<MUX1 | 1<<MUX0;

    //Enable interrupts function in ADC
    ADCSRA |= 1<<ADIE;

    //8-bit or 10-bit results (ADLAR = 1 for 8 bit)
    ADMUX |= 1<<ADLAR;

    //Enable a prescaler
    ADCSRA |= 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;

    //Turn on the ADC feature
    ADCSRA |= 1<<ADEN;



    //Enable the global interrupts
    sei();

    //Start the first conversion
    ADCSRA |= 1<<ADSC;

    //Confiugre the PWM
    TCCR1 |= 1<<CS12 | 1<<CS11; //divby32
    GTCCR |= 1<<PWM1B; //enable PWM mode output1B
    GTCCR |= 1<<COM1B1; //OC1B cleared on compare match
    DDRB |= 1<<PB4;

    while (1)
    {
        //update LED brightness

    }        

}

//*******Add the interrupt routine and display the results
ISR(ADC_vect)
{
//Set Duty Cycle to ADC result
    OCR1B = ADCH;


//Start the next conversion
    ADCSRA |= 1<<ADSC;
}

