/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #2  Exercise #4
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
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    while(1)
    {
		unsigned char tempA = PINA;
		unsigned char x = 0;
		unsigned char y = 0;
		unsigned char t = 0;
		for(unsigned char i = 0; i < 4; i++)
		{
			if(GetBit(tempA,i))
			{
				x = SetBit(x,i,1);
			}
			else
			{
				x = SetBit(x,i,0);
			}
			x << 1;
			
			t = i+4;
			if(GetBit(tempA,t))
			{
				y = SetBit(y,i,1);
			}
			else
			{
				y = SetBit(y,i,0);
			}
			y << 1;
			t++;
		}
		PORTB = y;
		x = x << 4;
		PORTC = x;
											
        //TODO:: Please write your application code 
    }
}