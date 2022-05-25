/*
 * Tranciever.cpp
 *
 * Created: 25-05-2022 11:26:10
 * Author : Frederik
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "Transciever.h"
#include "UART.h"


Transciever master;
long tvSignal;
volatile char modtaget;


void initInterupt0();
void initIOpins();




ISR(INT0_vect)
{
	master.setZeroCross(1);
	
	//// timer
	TCNT1 = 64147;				// tid til overflow = 5,556 ms
	TCCR1A |= 0b00000000;		// starter timer
	TCCR1B |= 0b00000011;		// Prescale på 64
	
}

ISR(USART0_RX_vect)
{
	modtaget = UDR0;
}

ISR(TIMER1_OVF_vect)
{
	TCCR1B = 0b00000000; // slut timer
	
	int nyesteBit;
	int ADClastRead;
	
	////ADC start
	ADMUX |= 0b00000001;   //ADC1
	ADCSRA |= 0b01000000;	
	while (ADCSRA & 0b01000000)
	{}
	int ADCread = ADCW;
	////ADC slut
	
	////sætter nyeste bit alt efter hvad adc giver af værdi
	if (((ADCread > ADClastRead) && (ADCread > 10)) || (ADCread > 50))
	{
		nyesteBit = 1;
	}
	else
	{
		nyesteBit = 0;
	}
	ADClastRead = ADCread;
	
	tvSignal = tvSignal << 1;
	tvSignal |= nyesteBit;
	
	switch(tvSignal)
	{
		case 0b11101010100111:
			PORTB = PINB | 0b00000001;
			tvSignal = 0;
			break;
		case 0b11100101010111:
			PORTB = PINB & 0b11111110;
			tvSignal = 0;
			break;
		default:
			break;
	}
}


int main(void)
{
	initIOpins();
	initInterupt0();
	UART uart0;
	
	uart0.SendString("Program startet.\f\n\n\n\r");
	uart0.SendString("_________________________________________________  \n\n\r");
	uart0.SendString("    X         X       X                  X X X X   \n\r");
	uart0.SendString("   X X        X       X                        X   \n\r");
	uart0.SendString("  X   X       X       X    X X X X X     X X X X   \n\r");
	uart0.SendString(" X X X X       X     X                   X         \n\r");
	uart0.SendString("X       X       X X X                    X X X X   \n\n\n\r");
	uart0.SendString("");
	uart0.SendString("X       X      X X X      X        X      X X X X  \n\r");
	uart0.SendString("X       X     X     X     X X    X X      X        \n\r");
	uart0.SendString("X X X X X    X       X    X  X  X  X      X X X    \n\r");
	uart0.SendString("X       X     X     X     X   XX   X      X        \n\r");
	uart0.SendString("X       X      X X X      X        X      X X X X  \n\r");
	uart0.SendString("__________________________________________________ \n\n\r");
	uart0.SendString("Taend lys:      Tast '1'                           \n\r");
	uart0.SendString("Sluk lys:       Tast '2'                           \n\r");
	uart0.SendString("Rul gardin op:  Tast '3'                           \n\r");
	uart0.SendString("Rul gardin ned: Tast '4'                           \n\r");
	uart0.SendString("Sluk Hjem:      Tast '5'                           \n\r");
	uart0.SendString("__________________________________________________ \n\r");
	
	/* Replace with your application code */
	while (1)
	{
		
		
		if ((modtaget == '1') || (modtaget == '2') || (modtaget == '3') || (modtaget == '4') || (modtaget == '5'))
		{
			switch (modtaget)
			{
				case '1':
				{
					uart0.SendString("Lampen taendes.\n\r");
					int adresse[6] = {0,1,0,1,0,1};
					master.setAdresse(adresse);
					int kommando[6] = {1,0,1,0,1,0};
					master.setKommando(kommando);
				}
				break;
				
				case '2':
				{
					uart0.SendString("Lampen slukkes\n\r");
					int adresse[6] = {0,1,0,1,0,1};
					master.setAdresse(adresse);
					int kommando[6] = {0,1,0,1,0,1};
					master.setKommando(kommando);
				}
				break;
				case '3':
				{
					uart0.SendString("Gardin rulles op\n\r");
					int adresse[6] = {1,0,0,1,1,0};
					master.setAdresse(adresse);
					int kommando[6] = {1,0,1,0,1,0};
					master.setKommando(kommando);
				}
				break;
				case '4':
				{
					uart0.SendString("Gardin rulles ned\n\r");
					int adresse[6] = {1,0,0,1,1,0};
					master.setAdresse(adresse);
					int kommando[6] = {0,1,0,1,0,1};
					master.setKommando(kommando);
				}
				break;
				case '5':
				{
					uart0.SendString("Hjem lukkes ned\n\r");
					int adresse[6] = {1,0,0,1,1,0};
					master.setAdresse(adresse);
					int kommando[6] = {0,1,0,1,0,1};
					master.setKommando(kommando);
				}
				default:
				break;
			}
			
			master.setZeroCross(0);
			
			master.sendStartBits();
			master.sendAdresseBits();
			master.sendKommandoBits();
			master.sendStopBits();
			
			if (modtaget == '5')
			{
				master.setZeroCross(0);
				
				int adresse[6] = {0,1,0,1,0,1};
				master.setAdresse(adresse);
				master.sendStartBits();
				master.sendAdresseBits();
				master.sendKommandoBits();
				master.sendStopBits();
			}
			
			PORTB = PINB ^ 0b11111111;

		}
		modtaget = '0';
		
	}
}

void initInterupt0()
{
	sei();
	EIMSK |= 0b00000001;
	EICRA |= 0b00000001;
}

void initIOpins()
{
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
}