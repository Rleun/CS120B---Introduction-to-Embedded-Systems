/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #2  Exercise #5
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/



#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01;
    while(1)
    {
        unsigned char tempD = PIND;
		unsigned char tempB = PINB;
		unsigned long weight = 0;
		weight = tempD;
		weight = weight << 1;
		if(GetBit(tempB,0))
		{
			weight = SetBit(weight,0,1);
		}
		
		if(weight >= 70)
		{
			tempB = SetBit(tempB,1,1);
			tempB = SetBit(tempB,2,0);
		}
		else if((weight > 5) && (weight < 70))
		{
			tempB = SetBit(tempB,2,1);
			tempB = SetBit(tempB,1,0);
		}
		else
		{
			tempB = SetBit(tempB,2,0);
			tempB = SetBit(tempB,1,0);
		}
		PORTB = tempB;						
    }
}