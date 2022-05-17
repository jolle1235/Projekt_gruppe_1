/*
 * Transmitter.cpp
 *
 * Created: 16-05-2022 12:01:15
 * Author : Frederik
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "UART.h"

ISR(INT0_vect);
ISR(USART0_RX_vect);
void initInterupt0();
void initIOpins();


int startbit[4] = {1,1,1,0};
int stopbit[4] = {0,1,1,1};
volatile int zeroCross = 0;
volatile char modtaget;

int main(void)
{

	initIOpins();
	initInterupt0();
	UART uart0;
	int adresse[6];
	int kommando[6];
	
    /* Replace with your application code */
    while (1) 
    {
		//char streng[] = "abcde";
		//while (streng != 0)
		//{
			//while((0b00100000 & UCSR0A) == 0)
			//{}
			//UDR0 = streng;
			//streng++;
		//}
		while (1)
		{
			if ((modtaget == 'a') || (modtaget == 'b') || (modtaget == 'c') || (modtaget == 'd'))
			{
				switch (modtaget)
				{
				case 'a':
					uart0.SendString("Lampen er t�ndt");
					adresse[0] = 0;
					adresse[1] = 1;
					adresse[2] = 0;
					adresse[3] = 1;
					adresse[4] = 0;
					adresse[5] = 1;
					kommando[0] = 1;
					kommando[1] = 0;
					kommando[2] = 1;
					kommando[3] = 0;
					kommando[4] = 1;
					kommando[5] = 0;
					for (int i = 0; i < 6; i++)
					{
						UDR0 = adresse[i];
						_delay_ms(500);
						PORTB = PINB ^ (adresse[i]<<i);
					}
					break;
				}
				UDR0 = modtaget;
				uart0.SendString("Hej");
				_delay_ms(1000);
			}
		}
		
		

		
		for (int i = 0; i < 4; i++)
		{
			while (zeroCross==0)
			{}
			PORTC = startbit[i];
			TCCR0A |= 0b00000000;
			TCCR0B |= 0b00000010;
			while ((TIFR0 & (1<<0)) == 0)
			{}
			PORTC = 0;
			TCCR0B |= 0b00000000;
			TIFR0 = 0b00000001;
			zeroCross = 0;
		}

		for (int i = 0; i < 6; i++)
		{
			while (zeroCross==0)
			{}
			PORTC = adresse[i];
			TCCR0A |= 0b00000000;
			TCCR0B |= 0b00000010;
			while ((TIFR0 & (1<<0)) == 0)
			{}
			PORTC = 0;
			TCCR0B |= 0b00000000;
			TIFR0 = 0b00000001;
			zeroCross = 0;
		}		
		
		for (int i = 0; i < 6; i++)
		{
			while (zeroCross==0)
			{}
			PORTC = kommando[i];
			TCCR0A |= 0b00000000;
			TCCR0B |= 0b00000010;
			while ((TIFR0 & (1<<0)) == 0)
			{}
			PORTC = 0;
			TCCR0B |= 0b00000000;
			TIFR0 = 0b00000001;
			zeroCross = 0;
		}
		
		
		for (int i = 0; i < 4; i++)
		{
			while (zeroCross==0)
			{}
			PORTC = stopbit[i];
			TCCR0A |= 0b00000000;
			TCCR0B |= 0b00000010;
			while ((TIFR0 & (1<<0)) == 0)
			{}
			PORTC = 0;
			TCCR0B |= 0b00000000;
			TIFR0 = 0b00000001;
			zeroCross = 0;
		}
		

		while (1)
		{
			PORTB = 0xFF;
		}
    }
}

ISR(INT0_vect)
{
	zeroCross = 1;
	PORTB = PINB ^ 0b10000000;
}

ISR(USART0_RX_vect)
{
	modtaget = UDR0;
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