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

unsigned char CountOnes(unsigned char x, unsigned char y, unsigned char z) 
{
 unsigned char count;
 count = 0;
 if (x == 1) 
 {
   count = count + 1;
 }
 if (y == 1) 
 {
   count = count + 1;
 }
 if (z == 1) 
 {
   count = count + 1;
 }
 return count;
}

void main() 
{
   while (1) 
   {
      B = CountOnes(A0, A1, A2); // function call
   }
}
