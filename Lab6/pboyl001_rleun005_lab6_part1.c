/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #6  Exercise #1
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/



#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char threeLEDs = 0;
unsigned char blinkingLED = 0;
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

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

enum SM1_States { SM1_s1, SM1_s2, SM1_s3, Init } SM1_State;

void TickFct_State_machine_1() {
	switch(SM1_State) { // Transitions
		case Init:
		SM1_State = SM1_s1;
		break;
		case SM1_s1:
		if (1) {
			SM1_State = SM1_s2;
		}
		break;
		case SM1_s2:
		if (1) {
			SM1_State = SM1_s3;
		}
		break;
		case SM1_s3:
		if (1) {
			SM1_State = SM1_s1;
		}
		break;
		default:
		SM1_State = SM1_s1;
	} // Transitions

	threeLEDs = threeLEDs & 0xF8;
	switch(SM1_State) { // State actions
		case SM1_s1:
		threeLEDs = threeLEDs | 0x01;
		break;
		case SM1_s2:
		threeLEDs =threeLEDs | 0x02;
		break;
		case SM1_s3:
		threeLEDs =threeLEDs | 0x04;
		break;
		default: // ADD default behaviour below
		break;
	} // State actions

}


enum SM2_States { SM2_LedOff, SM2_LedOn, Init2 } SM2_State;
unsigned char tempB;

void TickFct_State_machine_2() {
	/*VARIABLES MUST BE DECLARED STATIC*/
	/*e.g., static int x = 0;*/
	/*Define user variables for this state machine here. No functions; make them global.*/
	switch(SM2_State) { // Transitions
		case Init2:
		SM2_State = SM2_LedOff;
		break;
		case SM2_LedOff:
		if (1) {
			SM2_State = SM2_LedOn;
		}
		break;
		case SM2_LedOn:
		if (1) {
			SM2_State = SM2_LedOff;
		}
		break;
		default:
		SM2_State = SM2_LedOff;
	} // Transitions

	//tempB = PINB;
	switch(SM2_State) { // State actions
		case SM2_LedOff:
		blinkingLED = blinkingLED | 0x08;
		break;
		case SM2_LedOn:
		blinkingLED = blinkingLED & 0xF7;
		break;
		default: // ADD default behaviour below
		break;
	} // State actions
}

enum SM3_States {Init3, Output} SM3_State;

void OutputB()
{
	switch(SM3_State)
	{
		case Init3:
			SM3_State = Output;
			break;
		case Output:
			SM3_State = Output;
			break;
		default:
			SM3_State = Init;
			break;
	}
	
	PORTB = 0;
	switch(SM3_State)
	{
		case Init3:
			break;
		case Output:
			PORTB = blinkingLED | threeLEDs;

			break;
		default:
			break;
	}
}

int main() {

	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
		
	SM1_State = Init; // Initial state
	SM2_State = Init2;
	while(1) {
		TickFct_State_machine_1();
		TickFct_State_machine_2();
		OutputB();
		while(!TimerFlag);
		TimerFlag = 0;
	} // while (1)
} // Main
