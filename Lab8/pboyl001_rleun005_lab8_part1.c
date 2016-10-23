/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #8  Exercise #1
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>

unsigned char A1, A2, A3 = 0;
enum noteStates {noteInit, noteWait, noteC, noteD, noteE} noteState;

void set_PWM(double frequency)
{
	if(!frequency) {TCCR3B &= 0x08; }
	else {TCCR3B |= 0x03; }
		
	if(frequency < 0.954) { OCR3A = 0xFFFF; }
		
	else if (frequency > 31250) {OCR3A = 0x0000; }
		
	else {OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
		
	//sTCNT3 = 0;
}

void PWM_on()
{
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off()
{
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void TickNote()
{
	double cNote = 261.63;
	double dNote = 293.66;
	double eNote = 329.63;
		
	switch(noteState)
	{
		case noteInit:
			noteState = noteWait;
			break;
		case noteWait:
			if(A1 && !A2 && !A3)
			{
				noteState = noteC;
			}
			else if (!A1 && A2 && !A3)
			{
				noteState = noteD;
			}
			else if(!A1 && !A2 && A3)
			{
				noteState = noteE;
			}
			else
			{
				noteState = noteWait;
			}
		break;
		case noteC:
				if(A1 && !A2 && !A3)
				{
					noteState = noteC;
				}
				else
				{
					noteState = noteWait;
				}
			break;
		case noteD:
				if(!A1 && A2 && !A3)
				{
					noteState = noteD;
				}
				else
				{
					noteState = noteWait;
				}
			break;
		case noteE:
				if(!A1 && !A2 && A3)
				{
					noteState = noteE;
				}
				else
				{
					noteState = noteWait;
				}
			break;
		default:
				noteState = noteInit;
				break;
	}
	
	switch(noteState)
	{
		case noteInit:
			break;
		case noteWait:
			set_PWM(0);
			break;
		case noteC:
			set_PWM(cNote);
			break;
		case noteD:
			set_PWM(dNote);
			break;
		case noteE:
			set_PWM(eNote);
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	noteState = noteInit;
	
	PWM_on();
    while(1)
    {
        A1 = ~PINA & 0x01;
		A2 = (~PINA & 0x02) >> 1;
		A3 = (~PINA & 0x04) >> 2;
		
		TickNote();
    }
}
