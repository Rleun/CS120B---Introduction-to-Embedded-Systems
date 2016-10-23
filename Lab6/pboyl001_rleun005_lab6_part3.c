/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #6  Exercise #3
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count1;
unsigned char count2;
unsigned char count3;
unsigned char tempA;

unsigned char threeLEDs = 0;
unsigned char blinkingLED = 0;
unsigned char buzzer = 0;
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

enum SM4_States {Init4, Output} SM4_State;

void OutputB()
{
	switch(SM4_State)
	{
		case Init4:
			SM4_State = Output;
			break;
		case Output:
			SM4_State = Output;
			break;
		default:
			SM4_State = Init;
			break;
	}
	
	PORTB = 0;
	switch(SM4_State)
	{
		case Init4:
			break;
		case Output:
			PORTB = blinkingLED | threeLEDs | buzzer;
			break;
		default:
			break;
	}
}

enum BuzzFunction {Initial, WaitforA, BuzzOn, BuzzOff} BuzzState;

void Buzzfunct()
{
	switch(BuzzState)
	{
		case Initial:
			BuzzState = WaitforA;
			break;
		case WaitforA:
			if(tempA)
			{
				BuzzState = BuzzOn;
			}
			else
			{
				BuzzState = WaitforA;
			}
			break;
		case BuzzOn:
			if(tempA)
			{
				BuzzState = BuzzOff;
			}
			else
			{
				BuzzState = WaitforA;
			}
			break;
		case BuzzOff:
			if(tempA)
			{
				BuzzState = BuzzOn;
			}
			else
			{
				BuzzState = WaitforA;
			}
			break;
		default:
			BuzzState = Initial;
	}
	
	switch(BuzzState)
	{
		case Initial:
			break;
		case WaitforA:
			buzzer = 0;
			break;
		case BuzzOn:
			buzzer = buzzer | 0x10;
			break;
		case BuzzOff:
			buzzer = 0;
			break;
		default:
			break;
	}
}

int main() {

	DDRB = 0xFF;
	PORTB = 0x00;
	DDRA = 0x00;
	PORTA = 0xFF;
	TimerSet(1);
	TimerOn();
	
	count1 = 0;
	count2 = 0;
	count3 = 0;
	
	SM1_State = Init; // Initial state
	SM2_State = Init2;
	while(1) {
		tempA = (~PINA & 0x04) >> 2;
		count1++;
		count2++;
		count3++;
		OutputB();
		while(!TimerFlag);
		TimerFlag = 0;
		if(count1 == 300)
		{
			TickFct_State_machine_1();
			count1 = 0;
		}
		if(count2 == 1000)
		{
			TickFct_State_machine_2();
			count2 = 0;
		}	
		if(count3 == 1)
		{
			Buzzfunct();
			count3 = 0;
		}
		
	} // while (1)
} // Main
