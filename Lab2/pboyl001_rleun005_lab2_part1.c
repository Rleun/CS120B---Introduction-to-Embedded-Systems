/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #2  Exercise #1
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

void main()
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as outputs, initialize to 0s
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char cnt;
	while (1) {
		unsigned char mask = 0x01;
		unsigned char button = PINA & mask;
		unsigned char button2 = PINB & mask;
		cnt=0;
		for (unsigned char i =0; i<8; i++) {
			if (GetBit(button, i)) {
				cnt++;
				
			}
			if (GetBit(button2, i)) {
				cnt++;
			}
			mask = mask << 1;
			button = PINA & mask;
			button2 = PINB & mask;
		}
		PORTC = cnt;
	}
}
