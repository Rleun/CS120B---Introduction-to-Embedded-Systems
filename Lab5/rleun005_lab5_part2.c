/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: None
*	Lab Section: 21
*	Assignment: Lab #5  Exercise #2
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/
#include <avr/io.h>
#include <avr/interrupt.h>

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

enum SM1_States { SM1_s1, SM1_s2, SM1_s3, SM1_s4, Init} SM1_State;
unsigned tempA;

void TickFct_State_machine_1() {
	switch(SM1_State) { // Transitions
		case Init:
		SM1_State = SM1_s1;
		break;
		case SM1_s1:
		if (!(tempA & 0x01)) {
			SM1_State = SM1_s2;
		}
		else if ((tempA & 0x01)) {
			SM1_State = SM1_s4;
		}
		break;
		case SM1_s2:
		if (!(tempA & 0x01)) {
			SM1_State = SM1_s3;
		}
		else if ((tempA & 0x01)) {
			SM1_State = SM1_s4;
		}
		break;
		case SM1_s3:
		if (!(tempA & 0x01)) {
			SM1_State = SM1_s1;
		}
		else if ((tempA & 0x01)) {
			SM1_State = SM1_s4;
		}
		break;
		case SM1_s4:
		if ((tempA & 0x01)) {
			SM1_State = SM1_s1;
		}
		break;
		default:
		SM1_State = SM1_s1;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_s1:
		PORTB = 0x01;
		break;
		case SM1_s2:
		PORTB = 0x02;
		break;
		case SM1_s3:
		PORTB = 0x04;
		break;
		case SM1_s4:
		break;
		default: // ADD default behaviour below
		break;
	} // State actions

}


int main() {

	DDRB = 0xFF;
	PORTB = 0x00;
	DDRA = 0x00;
	PORTA = 0xFF;
	TimerSet(300);
	TimerOn();
	
	SM1_State = Init; // Initial state
	
	while(1) {
		tempA = ~PINA;
		TickFct_State_machine_1();
		while(!TimerFlag);
		TimerFlag = 0;
	} // while (1)
} // Main
