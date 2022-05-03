/*
 * Interupt.c
 *
 * Created: 28-04-2022 13:35:35
 *  Author: Frederik
 */ 

#include "Interupt.h"
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>


int counter = 0;



void initIOpins()
{
	DDRF = 0xFF;		// F pins er udgange
	DDRD = 0;			// D Pins er indgange
	DDRB = 0xFF;
	PORTF = 0b00000000;	// sætter 0 på alle 	
}

void initINT0()
{

	EIMSK |= 0b00000001;
	EICRA |= 0b00000011;
	
	
}

void turnOnLight(){
	
	//cli();
	
	if(counter == 0){
		PORTB = 0b00000000;
	}
	if (counter == 1)
	{
		PORTB = 0b00000001;
	}
	if (counter == 2)
	{
		PORTB = 0b00000000;
	}
	if (counter == 3)
	{
		PORTB = 0b00000001;
	}
	if (counter == 4)
	{
		PORTB = 0b00000001;
	}
	if (counter == 5)
	{
		PORTB = 0b00000000;
		counter = 0;
		_delay_ms(2000);
		PORTB = 0b11111111;
	}
	
	_delay_ms(2000);
	
	counter++;
}

