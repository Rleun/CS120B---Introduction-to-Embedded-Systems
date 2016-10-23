/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #1  Exercise #3
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs,
	// initialize to 0s

    unsigned char cntavail = 0;
	
    while(1)
    {
		unsigned char mask = 0x01;
		cntavail = 4;
		if(PINA & mask)
		{
			cntavail--;
		}
		mask = mask << 1;
		if(PINA & mask)
		{
			cntavail--;
		}		
		mask = mask << 1;
		if(PINA & mask)
		{
			cntavail--;
		}	
		mask = mask << 1;
		if(PINA & mask)
		{
			cntavail--;
		}											
		if(cntavail == 0)
		{
			cntavail = 0x80;	
		}						
        PORTC = cntavail;	    
    }
}