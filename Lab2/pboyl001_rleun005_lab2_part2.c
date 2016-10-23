/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #2  Exercise #2
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>

int main(void)
{
    while(1)
    {
		unsigned char tempA = PINA;
		unsigned char tempC = PINC;
		PORTC = 0;
		if((tempA > 12))
		{
			PORTC = 0x3F;
		}
		else if((tempA > 9) && (tempA < 13))
		{
			PORTC = 0x3E;
		}		
		else if((tempA > 6) && (tempA < 10))
		{
			PORTC = 0x3C;
		}	  			
		else if((tempA > 4) && (tempA < 7))
		{
			PORTC = 0x38;
		}
		else if((tempA > 2) && (tempA < 5))
		{
			PORTC = 0x70;
		}
		else if((tempA > 0))
		{
			PORTC = 0x60;
		}
		else
		{
			PORTC = 0x40;
		}						
    }
}
