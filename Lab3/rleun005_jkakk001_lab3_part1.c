/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
 *	Partner 2 Name & E-mail: Jaijeet Kakkar - jkakk001@ucr.edu
 *	Lab Section: 23
 *	Assignment: Lab 3  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

enum B_States {B_s0, B_s1, Init, Wait, Wait2} B_State;

unsigned char tempA;

void B_Ftc()
{
	switch(B_State)
	{
		case Init:
			B_State = B_s0;
			break;
		case B_s0:
			if(tempA & 0x01)
			{
				B_State = Wait;
			}
			else if(tempA & 0x00)
			{
				B_State = B_s0;
			}
			break;
		case B_s1:
			if(tempA & 0x01)
			{
				B_State = Wait2;
			}
			else if(tempA == 0x00)
			{
				B_State = B_s1;
			}
			break;
		case Wait:
			if(tempA == 0x00)
			{
				B_State = B_s1;
			}
			else
			{
				B_State = Wait;
			}
			break;
		case Wait2:
			if(tempA == 0x00)
			{
				B_State = B_s0;
			}
			else
			{
				B_State = Wait2;
			}
			break;
		default:
			B_State = Init;
			break;			
	}
	
	switch(B_State)
	{
		case B_s0:
			PORTB = 0x01;
			break;
		case B_s1:
			PORTB = 0x02;
			break;
		default:
			break;
	}				
	
}

void main(void)
{
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0xFF; PORTB = 0x00;
   
   B_State = Init;
   
   while(1)
   {
	   tempA = PINA;
	   B_Ftc();
   }
}