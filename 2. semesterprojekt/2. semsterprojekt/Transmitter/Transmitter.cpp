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
	if (x == 1 || x == 0)		//Dette er lavet så zeroCross kun kan blive 1 eller 0
	{
		zeroCross = x;
	}
}

void Transmitter::setAdresse(int array[])
{
	for (int i = 0; i < 6; i++)		// Sætter adressebits
	{
		adresse_[i] = array[i];
	}
}

void Transmitter::setKommando(int array[])
{
	for (int i = 0; i < 6; i++)		// Sætter kommandobits
	{
		kommando_[i] = array[i];
	}
}

void Transmitter::sendStartBits()
{
	for (int i = 0; i < 4; i++)			// Sender 4 bits (Startbit)
	{
		while (zeroCross==0)			// Venter på at der kommer et zerocross
		{PORTB = PINB | 0b00000001;}
		PORTC = startbit_[i];			// Sender den næste værdi ud på PORTC
		start1msDelay();				// Venter 1 ms, skaber burst i 1ms
		PORTC = 0;						// Slukker for burst
		stop1msDelay();					// Stopper timeren der står for at lave delay
		zeroCross = 0;					// Nulstiller zeroCross, så den er klar til næste interrupt
	}
}


void Transmitter::sendAdresseBits()
{
	for (int i = 0; i < 6; i++)			// Sender 6 bits (Adressen)
	{
		while (zeroCross==0)			// Venter på at der kommer et zerocross
		{PORTB = PINB | 0b00000010;}
		PORTC = adresse_[i];			// Sender den næste værdi ud på PORTC
		start1msDelay();				// Venter 1 ms, skaber burst i 1ms
		PORTC = 0;						// Slukker for burst
		stop1msDelay();					// Stopper timeren der står for at lave delay
		zeroCross = 0;					// Nulstiller zeroCross, så den er klar til næste interrupt
	}
}
	
void Transmitter::sendKommandoBits()
{
	for (int i = 0; i < 6; i++)			// Sender 6 bits (Kommando)
	{
		while (zeroCross==0)			// Venter på at der kommer et zerocross
		{PORTB = PINB | 0b00000100;}
		PORTC = kommando_[i];			// Sender den næste værdi ud på PORTC
		start1msDelay();				// Venter 1 ms, skaber burst i 1ms
		PORTC = 0;						// Slukker for burst
		stop1msDelay();					// Stopper timeren der står for at lave delay
		zeroCross = 0;					// Nulstiller zeroCross, så den er klar til næste interrupt
	}
}

void Transmitter::sendStopBits()
{
	for (int i = 0; i < 4; i++)			// Sender 4 bits (Stopbits)
	{
		while (zeroCross==0)			// Venter på at der kommer et zerrocross
		{PORTB = PINB | 0b00001000;}
		PORTC = stopbit_[i];			// Sender den næste værdi ud på PORTC
		start1msDelay();				// Venter 1 ms, skaber burst i 1ms
		PORTC = 0;						// Slukker for burst
		stop1msDelay();					// Stopper timeren der står for at lave delay
		zeroCross = 0;					// Nulstiller zeroCross, så den er klar til næste interrupt
	}
}

void Transmitter::start1msDelay()
{
	TCNT0 = 240;						// Sætter en værdi så det vil tage 1 ms at lave overflow
	TCCR0A |= 0b00000000;				// Sætter timeren til normalmode
	TCCR0B |= 0b00000101;				// Sætter prescalleren til 1024
	while ((TIFR0 & (1<<0)) == 0)		// Venter på at timeren laver overflow
	{}
}

void Transmitter::stop1msDelay()		// Slukker for timeren
{
	TCCR0B = 0b00000000;
	TIFR0 = 0b00000001;
}