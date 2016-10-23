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

unsigned char GetBit(unsigned char x, unsigned char k)
{
    return ((x & (0x01) << k) != 0);
}

void main()
{

   unsigned char i;
   while (1) { 
      unsigned char cnt = 0;
      unsigned char x = A;
      B0=0;
      for(i = 0; i < 8; i++)
      {
          if(GetBit(A,i))
          {
              cnt++;
          }
          else
          {
              cnt = 0;
          }
          if(cnt == 3)
          {
              B0 = 1;
          }
      }
      while(A == x) //Wait for A to change
      {}
   }
}
