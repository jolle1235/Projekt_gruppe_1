/* 
* TransmitterTV.cpp
*
* Created: 25-05-2022 11:51:42
* Author: jespe
*/


#include "TransmitterTV.h"

// default constructor
TransmitterTV::TransmitterTV()
{
	zeroCross_ = 0;
	startBits_[4] = 0b1110;
	KommandoBits_[6] = 0b101010;
	stopBits_[4] = 0b0111;
	
} //TransmitterTV

// default destructor
TransmitterTV::~TransmitterTV()
{
} //~TransmitterTV

int TransmitterTV::getZeroCross(){
	return zeroCross_;
	
}
void TransmitterTV::setZeroCross(int zeroCross){
	zeroCross_ = zeroCross;
		
	}
void TransmitterTV::sendStartBits(){
		for (int i = 0; i < 4; i++)
		{
			while (zeroCross_==0)
			{PORTB = PINB | 0b00000001;}
			PORTC = startBits_[i];
			PORTC = 0;
			zeroCross_ = 0;
		}
		
	}
void TransmitterTV::sendKommandoBits(){
		for (int i = 0; i < 6; i++)
		{
			while (zeroCross_ == 0)
			{PORTB = PINB | 0b00000100;}
			PORTC = KommandoBits_[i];
		
			PORTC = 0;
			zeroCross_ = 0;
		}
		
	}
	
void TransmitterTV::sendStopBits(){
	
	
}

	
void TransmitterTV::startDelay(){
	TCNT1 = 64147;
	TCCR1A |= 0;
	TCCR1B |= 0b00000011;
		
	}
void TransmitterTV::stopDelay(){
	TCCR1B = 0b00000000;
		
	}
int TransmitterTV::checkIfTurnedOn(){
		
		
	}
