/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #8  Exercise #2
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>

unsigned char A1, A2, A3 = 0;
unsigned char i = 0;
enum noteStates {noteInit, noteWait, notePlay} noteState;
enum changeNoteStates {changeNoteInit, changeNoteWait, changeNoteInc, changeNoteDec} changeNoteState;
	
double notes[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

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
	switch(noteState)
	{
		case noteInit:
			noteState = noteWait;
			break;
		case noteWait:
			if(A1)
			{
				noteState = notePlay;
			}
			else
			{
				noteState = noteWait;
			}
			break;
		case notePlay:
			if(A1)
			{
				noteState = notePlay;
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
		case notePlay:
			set_PWM(notes[i]);
			break;
		default:
			break;
	}
}

void TickNoteChange()
{
	switch(changeNoteState)
	{
		case changeNoteInit:
			changeNoteState = changeNoteWait;
			break;
		case changeNoteWait:
			if(A2 && !A3)
			{
				changeNoteState = changeNoteInc;
				if(i < 7)
				{
					i++;
				}
				else
				{
					i = 7;
				}
			}
			else if(!A2 && A3)
			{
				changeNoteState = changeNoteDec;
				if(i > 0)
				{
					i--;
				}
			}
			else
			{
				changeNoteState = changeNoteWait;
			}
			break;
		case changeNoteInc:
			if(A2)
			{
				changeNoteState = changeNoteInc;
			}
			else
			{
				changeNoteState = changeNoteWait;
			}
			break;
		case changeNoteDec:
			if(A3)
			{
				changeNoteState = changeNoteDec;
			}
			else
			{
				changeNoteState = changeNoteWait;
			}
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
		TickNoteChange();
    }
}
