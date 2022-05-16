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

ISR(INT0_vect);
void initInterupt0();
void initIOpins();


int startbit[4] = {1,1,1,0};
int stopbit[4] = {0,1,1,1};
volatile int zeroCross = 0;

int main(void)
{

	initIOpins();
	initInterupt0();
	
    /* Replace with your application code */
    while (1) 
    {
		
		
		int adresse[6] = {0,1,0,1,0,1};
		int kommando[6] = {1,0,1,0,1,0};
		
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