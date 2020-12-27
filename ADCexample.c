/*
 * tinyADC.c
 *
 * Created: 12/20/2020 16:39
 * Author: Jeff
 */

#define F_CPU  8000000

#include <avr/io.h>
#include <avr/interrupt.h>

double dutyCycle = 0;

int main(void)
{
	DDRB = (1 << PB3);

	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);

	setupADC();

	sei();

	TCCR0B = (1 << CS00) | (1 << CS02);

  while(1)
  {
  //TODO:: Please write your application code
  }
}

void setupADC()
{
    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    DIDR0 = (1 << ADC5D);

    startConversion();
}

void startConversion()
{
    ADCSRA |= (1 << ADSC);
}

ISR(TIMER0_OVF_vect)
{
    OCR0A = dutyCycle;
}

ISR(ADC_vect)
{
    dutyCycle = ADC;
    startConversion();
}
