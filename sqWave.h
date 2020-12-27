/*
 * sqWave.h
 *
 * Created: 2020-12-06 2020
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
 
#ifndef s_W
#define s_W 1
void initializeSqWave(void);

void startSqWave(void);

void stopSqWave(void);

void setOutputPortB(uint8_t outPin);

void runSqWave(uint16_t periodMatchCount, uint8_t outPin);


#endif
