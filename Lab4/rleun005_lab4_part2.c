/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: None
*	Lab Section: 21
*	Assignment: Lab #4  Exercise #2
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>


enum C_States {Wait, Plus, Minus, Init, Reset, Plus2, Minus2} C_State;

unsigned char tempA;

unsigned char cnt = 0;

void C_Ftc()
{
	switch(C_State)
	{
		case Init:
			C_State = Wait;
			break;
		case Wait:
			if((tempA == 0x01) && (tempA != 0x02))
			{
				C_State = Plus;
			}
			else if((tempA == 0x02) && (tempA != 0x01))
			{
				C_State = Minus;
			}
			else if(tempA == 0x03)
			{
				C_State = Reset;
			}
			else
			{
				C_State = Wait;
			}
			break;
		case Plus:
			if(tempA == 0x03)
			{
				C_State = Reset;
			}
			else 
			{
				C_State = Plus2;
			}
			break;
		case Minus:
			if(tempA == 0x03)
			{
				C_State = Reset;
			}
			else
			{
				C_State = Minus2;
			}
			break;	
					
		case Reset:
			C_State = Wait;
			break;
		case Plus2:
			if(!((tempA == 0x01) && (tempA != 0x02)))
			{
				C_State = Wait;
			}
			break;
		case Minus2:
			if(!((tempA == 0x02) && (tempA != 0x01)))
			{
				C_State = Wait;
			}
			break;
		default:
			C_State = Init;
			break;			
	}
	
	switch(C_State)
	{
		case Wait:
			PORTC = cnt;
			break;
		case Plus:
			if(cnt < 9)
			{
				cnt++;
			}				
			break;
		case Minus:
			if(cnt > 0)
			{
				cnt--;
			}
			break;
		case Reset:
			cnt = 0;
			break;
		default:
			break;
	}				
	
}

int main(void)
{
   DDRA = 0x00; PORTA = 0xFF;
   DDRC = 0xFF; PORTC = 0x00;
   
   C_State = Init;
   PORTC = 7;
   cnt = 7;
   while(1)
   {
	   tempA = ~PINA;
	   C_Ftc();
   }
}