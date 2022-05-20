/* 
* Transmitter.cpp
*
* Created: 17-05-2022 12:14:39
* Author: Frederik
*/


#include "Transmitter.h"

int Transmitter::startbit_[4] = {1,1,1,0};
int Transmitter::stopbit_[4] = {0,1,1,1};
	

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

void Transmitter::setAdresse(int array[])
{
	for (int i = 0; i < 6; i++)
	{
		adresse_[i] = array[i];
	}
}

void Transmitter::setKommando(int array[])
{
	for (int i = 0; i < 6; i++)
	{
		kommando_[i] = array[i];
	}
}

void Transmitter::sendStartBits()
{
	for (int i = 0; i < 4; i++)
	{
		while (zeroCross==0)
		{PORTB = PINB | 0b00000001;}
		PORTC = startbit_[i];
		start1msDelay();
		PORTC = 0;
		stop1msDelay();
		zeroCross = 0;
	}
}


void Transmitter::sendAdresseBits()
{
	for (int i = 0; i < 6; i++)
	{
		while (zeroCross==0)
		{PORTB = PINB | 0b00000010;}
		PORTC = adresse_[i];
		start1msDelay();
		PORTC = 0;
		stop1msDelay();
		zeroCross = 0;
	}
}
	
void Transmitter::sendKommandoBits()
{
	for (int i = 0; i < 6; i++)
	{
		while (zeroCross==0)
		{PORTB = PINB | 0b00000100;}
		PORTC = kommando_[i];
		start1msDelay();
		PORTC = 0;
		stop1msDelay();
		zeroCross = 0;
	}
}

void Transmitter::sendStopBits()
{
	for (int i = 0; i < 4; i++)
	{
		while (zeroCross==0)
		{PORTB = PINB | 0b00001000;}
		PORTC = stopbit_[i];
		start1msDelay();
		PORTC = 0;
		stop1msDelay();
		zeroCross = 0;
	}
}

void Transmitter::start1msDelay()
{
	TCNT0 = 240;
	TCCR0A |= 0b00000000;
	TCCR0B |= 0b00000101;
	while ((TIFR0 & (1<<0)) == 0)
	{}
}

void Transmitter::stop1msDelay()
{
	TCCR0B = 0b00000000;
	TIFR0 = 0b00000001;
}