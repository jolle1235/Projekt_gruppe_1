/* 
* Reciever.cpp
*
* Created: 17-05-2022 12:57:08
* Author: jespe
*/


#include "RecieverLamp.h"
#include "UART.h"

// default constructor
RecieverLamp::RecieverLamp()
{
	zeroCross_ = 0;
	nyesteBit_ = 0;
	seneste6Bits_ = 0b000000;
	startBits_ = 0b1110;
	stopBits_ = 0b0111;
	adresseBits_ = 0b010101; // 111 / 000 binær
	kommandoBits_ = 0b101010; //
	
} 

// default destructor
RecieverLamp::~RecieverLamp()
{
	
} 
int RecieverLamp::getZeroCross()
{
	return zeroCross_;
}
void RecieverLamp::setZeroCross(int zeroCross)
{
	zeroCross_ = zeroCross;
}

int RecieverLamp::getNyesteBit()
{
		return nyesteBit_;		
}
void RecieverLamp::setNyesteBit(int nyestebit)
{
		
}

int RecieverLamp::readStartBits(){
	
	while(startBits_ != seneste6Bits_){
			if (zeroCross_ == 1)
			{
				readADC();
				
				seneste6Bits_ << 1;
				seneste6Bits_ |= nyesteBit_; 
			
				zeroCross_ = 0;
				// PORTB ^= (1<<6);		bruges til at teste
				
			}
	}
	
	return 1;
	
}
int RecieverLamp::readAdresseBits(){
	while(adresseBits_ != seneste6Bits_){
		if (zeroCross_ == 1)
		{
			readADC();
			
			seneste6Bits_ << 1;
			seneste6Bits_ |= nyesteBit_;
			
			zeroCross_ = 0;
			// PORTB ^= (1<<6);		bruges til at teste
			
		}
	}
	
	return 1;
	
}
int RecieverLamp::readDataBits(){
	while(kommandoBits_ != seneste6Bits_){
		if (zeroCross_ == 1)
		{
			readADC();
			
			seneste6Bits_ << 1;
			seneste6Bits_ |= nyesteBit_;
			
			zeroCross_ = 0;
			// PORTB ^= (1<<6);		bruges til at teste
			
		}
	}
	
	return 1;
	
}
int RecieverLamp::readStopBits(){
	while(stopBits_ != seneste6Bits_){
		if (zeroCross_ == 1)
		{
			readADC();
			
			seneste6Bits_ << 1;
			seneste6Bits_ |= nyesteBit_;
			
			zeroCross_ = 0;
			// PORTB ^= (1<<6);		bruges til at teste
			
		}
	}
	
	return 1;
}

void RecieverLamp::readADC(){
	ADCSRA |= 0b01000000;
	while (ADCSRA & 0b01000000)
	{}
	
	x = ADCW;
	uart_->SendInteger(x);
	//uart_->SendString("/");
	//uart_->SendInteger(x);
	
	
	if (x > 800)
	{
		setNyesteBit(1);
	}								//Dette er ikke testet, men virker måske
	else
	{
		setNyesteBit(0);
	}
	
	//if (PINF0 > 800)
	//{
		//setNyesteBit(1)
	//}								//Dette er ikke testet, men virker måske
	//else
	//{
		//setNyesteBit(0);
	//}
	
}

void RecieverLamp::turnOnLight()
{
	PORTB = 0b11111111;
}
