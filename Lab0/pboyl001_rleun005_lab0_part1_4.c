/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu 
 *	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
 *	Lab Section: 21
 *	Assignment: Lab #0  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 
#include "rims.h"

void LedsTick() {
 static unsigned char leds = 1;
 leds = (leds == 8) ? 1 : leds * 2;
 B = leds;
}

void main(){
 while(1){
 LedsTick();
 }
}