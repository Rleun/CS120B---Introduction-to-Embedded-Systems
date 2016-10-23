/*	Partner 1 Name & E-mail: Richel Leung - rleun005@ucr.edu
*	Partner 2 Name & E-mail: Patrick Boyle - pboyl001@ucr.edu
*	Lab Section: 21
*	Assignment: Lab #6  Exercise #4
*	Exercise Description: [optional - include for your own benefit]
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

enum Three_LED_States {Three_LED_init, Three_LED_oneOn, Three_LED_twoOn, Three_LED_threeOn} Three_LED_State;
enum Blinking_LED_States {Blinking_LED_init, Blinking_LED_blink, Blinking_LED_blinkOff} Blinking_LED_State;
enum Output_States {Output_init, Output_portb} Output_State;
enum Buzzer_States {Buzzer_init, Buzzer_waitButton, Buzzer_buzzerOn, Buzzer_buzzerOff} Buzzer_State;
enum Frequency_States {Frequency_init, Frequency_wait, Frequency_increment, Frequency_decrement,
						Frequency_waitBut1, Frequency_waitBut2} Frequency_State;

unsigned char threeLEDTemp = 0;
unsigned char blinkLEDTemp = 0;
unsigned char buzzerTemp = 0;
unsigned char buttonInput = 0;
unsigned char buttonInputA0 = 0;
unsigned char buttonInputA1 = 0;
unsigned char frequency = 1;

void TickFct_Three_LED()
{
	switch(Three_LED_State){
		case Three_LED_init:
			Three_LED_State = Three_LED_oneOn;
			break;
		case Three_LED_oneOn:
			Three_LED_State = Three_LED_twoOn;
			break;
		case Three_LED_twoOn:
			Three_LED_State = Three_LED_threeOn;
			break;
		case Three_LED_threeOn:
			Three_LED_State = Three_LED_oneOn;
			break;
		default:
			Three_LED_State = Three_LED_init;
			break;
	}
	
	threeLEDTemp = threeLEDTemp & 0xF8; //clear B0, B1, and B2 before updating.
	
	switch(Three_LED_State){
		case Three_LED_init:
			threeLEDTemp = 0x00;
			break;
		case Three_LED_oneOn:
			threeLEDTemp = threeLEDTemp | 0x01;
			break;
		case Three_LED_twoOn:
			threeLEDTemp = threeLEDTemp | 0x02;
			break;
		case Three_LED_threeOn:
			threeLEDTemp = threeLEDTemp | 0x04;
			break;
		default:
			break;
		
	}
}

void TickFct_Blinking_LED()
{
	switch(Blinking_LED_State)
	{
		case Blinking_LED_init:
			Blinking_LED_State = Blinking_LED_blink;
			break;
		case Blinking_LED_blink:
			Blinking_LED_State = Blinking_LED_blinkOff;
			break;
		case Blinking_LED_blinkOff:
			Blinking_LED_State = Blinking_LED_blink;
			break;
		default:
			Blinking_LED_State = Blinking_LED_init;
			break;
	}
	
	blinkLEDTemp = blinkLEDTemp & 0x07;
	
	switch(Blinking_LED_State)
	{
		case Blinking_LED_init:
			blinkLEDTemp = 0x00;
			break;
		case Blinking_LED_blink:
			blinkLEDTemp = blinkLEDTemp | 0x08;
			break;
		case Blinking_LED_blinkOff:
			blinkLEDTemp = blinkLEDTemp & 0x07;
			break;
		default:
			break;
	}
}

void TickFct_Output()
{
	switch(Output_State)
	{
		case Output_init:
			Output_State = Output_portb;
			break;
		case Output_portb:
			Output_State = Output_portb;
			break;
		default:
			Output_State = Output_portb;
			break;
	}
	
	switch(Output_State)
	{
		case Output_init:
			break;
		case Output_portb:
			PORTB = blinkLEDTemp | threeLEDTemp | buzzerTemp;
		default:
			break;
	}
}

void TickFct_Buzzer()
{
	switch(Buzzer_State)
	{
		case Buzzer_init:
			Buzzer_State = Buzzer_waitButton;
			break;
		case Buzzer_waitButton:
			if(buttonInput)
			{
				Buzzer_State = Buzzer_buzzerOn;
			}
			else
			{
				Buzzer_State = Buzzer_waitButton;
			}
			break;
		case Buzzer_buzzerOn:
			if(buttonInput)
			{
				Buzzer_State = Buzzer_buzzerOff;
			}
			else
			{
				Buzzer_State = Buzzer_waitButton;
			}
			break;
		case Buzzer_buzzerOff:
			if(buttonInput)
			{
				Buzzer_State = Buzzer_buzzerOn;
			}
			else
			{
				Buzzer_State = Buzzer_waitButton;
			}
			break;			
	}
	
	buzzerTemp = buzzerTemp & 0xEF;
	
	switch(Buzzer_State)
	{
		case Buzzer_init:
			break;
		case Buzzer_waitButton:
			break;
		case Buzzer_buzzerOn:
			buzzerTemp = buzzerTemp | 0x10;
			break;
		case Buzzer_buzzerOff:
			buzzerTemp = buzzerTemp & 0x00;
			break;
		default:
			break;
	}		
}

void TickFct_ChangeFrequency()
{
	switch(Frequency_State)
	{
		case Frequency_init:
			Frequency_State = Frequency_wait;
			break;
		case Frequency_wait:
			if(buttonInputA0 && !buttonInputA1)
			{
				frequency++;
				Frequency_State = Frequency_increment;
			}
			else if(!buttonInputA0 && buttonInputA1){
				if(frequency > 1)
				{
					frequency--;
				}
				else
				{
					frequency = 1;
				}
				Frequency_State = Frequency_decrement;
			}
			else
			{
				Frequency_State = Frequency_wait;
			}			
		break;
		case Frequency_increment:			
			if(buttonInputA0)
			{
				Frequency_State = Frequency_increment;
			}
			else
			{
				Frequency_State = Frequency_wait;
			}
			break;
		case Frequency_decrement:
			if(buttonInputA1)
			{
				Frequency_State = Frequency_decrement;
			}
			else
			{
				Frequency_State = Frequency_wait;
			}
			break;
		default:
			Frequency_State = Frequency_init;
			break;		
	}
}

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
	TimerISR(); // Call the ISR that the user uses
	_avr_timer_cntcurr = _avr_timer_M;
}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void main()
{
	DDRC = 0xFF;PORTC = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned short counterThree = 0;
	unsigned short counterBlink = 0;
	unsigned short counterFreq = 0; 
	
	counterBlink = 0;
	counterThree = 0;
	buttonInput = 0;
	
	TimerSet(1);
	TimerOn();
	Three_LED_State = Three_LED_init;
	Blinking_LED_State = Blinking_LED_init;
	while(1) {
		
		buttonInput = (~PINA & 0x04) >> 2;
		buttonInputA0 = ~PINA & 0x01;
		buttonInputA1 = (~PINA & 0x02) >> 1;
		
		TickFct_ChangeFrequency();
		
		if(counterFreq >= frequency)
		{
			counterFreq = 0;
			TickFct_Buzzer();	
		}
		else
		{
			counterFreq++;
		}
		
		if(counterThree >= 300)
		{
			counterThree = 0;
			TickFct_Three_LED();
		}
		else
		{
			counterThree++;
		}
		
		if(counterBlink >= 1000)
		{
			counterBlink = 0;
			TickFct_Blinking_LED();
		}
		else
		{
			counterBlink++;
		}
		
		TickFct_Output();
		
		TimerFlag = 0;
		while (!TimerFlag);	
	}
}
