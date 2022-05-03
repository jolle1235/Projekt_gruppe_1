/*
 * Interupt.c
 *
 * Created: 28-04-2022 13:35:35
 *  Author: Frederik
 */ 

#include "Interupt.h"


ISR(INT0_vect)
{
	PORTF = 0b00000001;
}

void initIOpins()
{
	DDRF = 0xFF;		// F pins er udgange
	DDRD = 0;			// D Pins er indgange
}

void initINT0()
{

	EIMSK |= 0b00000001;
	EICRA |= 0b00000011;
	
	
}

