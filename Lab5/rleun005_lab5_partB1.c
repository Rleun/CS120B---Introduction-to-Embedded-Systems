/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: None
*	Lab Section: 21
*	Assignment: Lab #5  Exercise #B1
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

unsigned char tempA;
unsigned char number;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn()
{
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff()
{
	TCCR1B = 0x00;
}

void TimerISR()
{
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}


enum SM1_States { SM1_s1, SM1_s2, SM1_s3, SM1_s4 , init} SM1_State;

void TickFct_State_machine_1() {
	switch(SM1_State) { // Transitions
		case init:
		SM1_State = SM1_s1;
		break;
		case SM1_s1:
		if ((tempA == 1)) {
			SM1_State = SM1_s2;
		}
		else if ((tempA == 2)) {
			SM1_State = SM1_s3;
		}
		else if ((tempA == 3)) {
			SM1_State = SM1_s4;
		}
		else {
			SM1_State = SM1_s1;
		}
		break;
		case SM1_s2:
		if ((tempA == 1)) {
			SM1_State = SM1_s2;
		}
		else if (!((tempA == 1) || (tempA == 3)) ) {
			SM1_State = SM1_s1;
		}
		else if ((tempA == 3)) {
			SM1_State = SM1_s4;
		}
		break;
		case SM1_s3:
		if ((tempA == 2)) {
			SM1_State = SM1_s3;
		}
		else if (!((tempA == 2) || (tempA == 3)) ) {
			SM1_State = SM1_s1;
		}
		else if ((tempA == 3)) {
			SM1_State = SM1_s4;
		}
		break;
		case SM1_s4:
		if (1) {
			SM1_State = SM1_s1;
		}
		break;
		default:
		SM1_State = SM1_s1;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_s1:
		break;
		case SM1_s2:
		if(number < 9)
		{
			number++;
		}
		break;
		case SM1_s3:
		if(number > 0)
		{
			number--;
		}
		break;
		case SM1_s4:
			number = 0;
		break;
		default: // ADD default behaviour below
		break;
	} // State actions

}

int main() {

	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	DDRA = 0x00; PORTA = 0xFF;
	
	SM1_State = init; // Initial state
	number = 0;
	LCD_init();
	TimerSet(1000);
	TimerOn();

	while(1) {
		tempA = ~PINA;
		TickFct_State_machine_1();
		LCD_Cursor(1);
		LCD_WriteData(number + '0');
		while(!TimerFlag);
		TimerFlag = 0;
	} // while (1)
} // Main

