/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: None
*	Lab Section: 21
*	Assignment: Lab #4  Exercise #3
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>

/*Define user variables and functions for this state machine here.*/
unsigned char SM1_Clk;
unsigned char tempA;
enum SM1_States { SM1_s1, SM1_s2, SM1_s3, SM1_s4, SM1_s5, SM1_s6 , t} SM1_State;

void TickFct_State_machine_1() {
	switch(SM1_State) { // Transitions
		case t:
		SM1_State = SM1_s1;
		break;
		case SM1_s1:
		if ((tempA & 0x01)) {
			SM1_State = SM1_s2;
		}
		break;
		case SM1_s2:
		if (!(tempA & 0x01)) {
			SM1_State = SM1_s3;
		}
		break;
		case SM1_s3:
		if ((tempA & 0x01)) {
			SM1_State = SM1_s4;
		}
		break;
		case SM1_s4:
		if (!(tempA & 0x01)) {
			SM1_State = SM1_s5;
		}
		break;
		case SM1_s5:
		if ((tempA & 0x01)) {
			SM1_State = SM1_s6;
		}
		break;
		case SM1_s6:
		if (!(tempA & 0x01)) {
			SM1_State = SM1_s2;
		}
		break;
		default:
		SM1_State = SM1_s1;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_s1:
		break;
		case SM1_s2:
		break;
		case SM1_s3:
		PORTC = 0xAA;
		break;
		case SM1_s4:
		break;
		case SM1_s5:
		PORTC = 0x55;
		break;
		case SM1_s6:
		break;
		default: // ADD default behaviour below
		break;
	} // State actions

}

int main() {

	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	SM1_State = t; // Initial state


	while(1) {
		tempA = ~PINA;
		TickFct_State_machine_1();

	} // while (1)
} // Main