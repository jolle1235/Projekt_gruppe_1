/* 
* Transmitter.cpp
*
* Created: 17-05-2022 12:14:39
* Author: Frederik
*/


#include "Transmitter.h"

int Transmitter::startbit[4] = {1,1,1,0};
	

// default constructor
Transmitter::Transmitter()
{
	zeroCross = 0;

} //Transmitter


int Transmitter::getZeroCross()
{
	return zeroCross;
}

void Transmitter::setZeroCross(int x)
{
	if (x == 1 || x == 0)
	{
		zeroCross = x;
	}
}

void Transmitter::sendStartBits()
{
	for (int i = 0; i < 4; i++)
	{
		while (zeroCross==0)
		{PORTB = PINB | 0b00000001;}
		PORTC = startbit[i];
		TCCR0A |= 0b00000000;
		TCCR0B |= 0b00000010;
		while ((TIFR0 & (1<<0)) == 0)
		{}
		//PORTC = 0;
		TCCR0B |= 0b00000000;
		TIFR0 = 0b00000001;
		zeroCross = 0;
	}
}


void Transmitter::sendAdresseBits()
{
	
}
	
void Transmitter::sendKommandoBits()
{
	
}

void Transmitter::sendStopBits()
{
	
}
