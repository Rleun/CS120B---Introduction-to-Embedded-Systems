/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
 *	Partner 2 Name & E-mail: Jaijeet Kakkar - jkakk001@ucr.edu
 *	Lab Section: 23
 *	Assignment: Lab 3  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

enum Lock_States {Init, Wait, IsPound, Wait2, Unlock, Lock} Lock_State;

unsigned char tempA;
unsigned char tempB;
void Lock_ftn()
{
	switch(Lock_State)
	{
		case Init:
			Lock_State = Wait;
			break;
		case Wait:
			if((tempA & 0x04) != 0)
			{
				Lock_State = IsPound;
			}
			else if ((tempA & 0x80) != 0)
			{
				Lock_State = Lock;
			}
			else
			{
				Lock_State = Wait;
			}
			break;
		case IsPound:
			if((tempA & 0x04) == 0)
			{
				Lock_State = Wait2;
			}
			else if ((tempA & 0x80) != 0)
			{
				Lock_State = Lock;
			}
			else
			{
				Lock_State = IsPound;
			}
			break;
		case Wait2:
			if((tempA & 0x02) != 0)
			{
				Lock_State = Unlock;
			}
			else if ((tempA & 0x80) != 0)
			{
				Lock_State = Lock;
			}
			else if(tempA == 0)
			{
				Lock_State = Wait2;
			}
			else
			{
				Lock_State = Wait;
			}
			break;
		case Unlock:
			Lock_State = Wait;
			break;
		default:
			Lock_State = Init;
			break;
	}
	
	switch(Lock_State)
	{
		case Lock:
			tempB = 0x00;
			PORTB = tempB;
			break;
		case Unlock:
			if(tempB == 0x00)
			{
				PORTB = 0x01;	
			}				
			else
			{
				PORTB = 0x00;
			}				
			break;
		default:
			break;
	}
	
}
int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	

    while(1)
    {
		PORTC = Lock_State;
		tempA = PINA;
		tempB = PINB;
		Lock_ftn();
    }
}