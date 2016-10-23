/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #7  Exercise #4
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}


int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	
	ADC_init();
	
	unsigned short input;
	unsigned char forB;
	unsigned char forD;
	unsigned short max = 0x001F;
	unsigned short maxDivided = max/8;
	
	while(1)
	{
		input = ADC;
		unsigned short temp = input/maxDivided;
		unsigned char forB = 0x00;
		while(temp > 0)
		{
			forB = forB << 1;
			forB = forB | 0x01;
			temp--;
		}
		PORTB = forB;
		//TODO:: Please write your application code
	}
}
