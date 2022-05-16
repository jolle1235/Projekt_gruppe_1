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

bool zeroCross = false;
int startbit[4] = {1,1,1,0};


int main(void)
{
	initIOpins();
	initInterupt0();
	
    /* Replace with your application code */
    while (1) 
    {
		for (int i = 0; i < 4; i++)
		{
			while (!zeroCross)
			{};
			PORTB = i;
			zeroCross = false;
		}
    }
}

ISR(INT0_vect)
{
	PORTB = PINB ^ 0b10000000;
	zeroCross = true;
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