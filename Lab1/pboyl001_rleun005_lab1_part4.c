/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu 
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #1  Exercise #4
*	Exercise Description: [optional - include for your own benefit]
*	
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as outputs,
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned short totalWeight = 0;
	unsigned short difference = 0;
    while(1)
    {
		PORTD = 0x00;
        totalWeight = PINA + PINB + PINC;
		if(totalWeight > 0x8C)
		{
			PORTD = 0x01;
			
		}
		else
		{
			if(PINA > PINC)
			{
				difference = PINA - PINC;
			}
			else
			{
				
				difference = PINC - PINA;
						
			}
			if(difference > 0x50)
			{
				
				PORTD = 0x02;
			}
			unsigned short weightLeft = 0x8C - totalWeight;
			unsigned char tempD = PIND;
			weightLeft = weightLeft & 0xFC;
			PORTD = weightLeft | tempD;
		}
		
    }
}