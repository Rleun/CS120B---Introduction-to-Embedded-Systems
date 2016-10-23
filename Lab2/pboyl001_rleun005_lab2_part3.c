/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #2  Exercise #3
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
    while(1)
    {
		unsigned char tempA = PINA;
		unsigned char tempC = 0;
		unsigned char mask = 0x10;
		unsigned char button = PINA & mask;
		PORTC = 0;
		if(GetBit(button,4))
		{
			unsigned char t1 = 0x0F;
			tempA = tempA & t1; 
			if((tempA > 12))
			{
				tempC = 0x3F;
			}
			else if((tempA > 9) && (tempA < 13))
			{
				tempC = 0x3E;
			}
			else if((tempA > 6) && (tempA < 10))
			{
				tempC = 0x3C;
			}
			else if((tempA > 4) && (tempA < 7))
			{
				tempC = 0x38;
			}
			else if((tempA > 2) && (tempA < 5))
			{
				tempC = 0x70;
			}
			else if((tempA > 0))
			{
				tempC = 0x60;
			}
			else
			{
				tempC = 0x40;
			}
			mask = mask << 1;
			button = PINA & mask;
			//tempC = PINC;
			if(GetBit(button,5))
			{
				mask = mask << 1;
				button = PINA & mask;
				if(!GetBit(button,6))
				{
					unsigned char t = 0x80;
					PORTC = tempC | t;	
				}
				else
				{
					PORTC = tempC;
				}
			}
			else
			{
				PORTC = tempC;
				
			}
			
		}			
    }
}
