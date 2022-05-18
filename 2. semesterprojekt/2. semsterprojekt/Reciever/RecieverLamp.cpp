/* 
* Reciever.cpp
*
* Created: 17-05-2022 12:57:08
* Author: jespe
*/


#include "RecieverLamp.h"


// default constructor
RecieverLamp::RecieverLamp()
{
	zeroCross_ = 0;
	nyesteBit_ = 0;
	ADCread_ = 0;
	ADClastRead_ = 0;
	seneste6Bits_ = 0b000000;
	startBits_ = 0b1110;
	stopBits_ = 0b0111;
	adresseBits_ = 0b010101; // 111 / 000 bin�r
	kommandoBits_ = 0b101010; //
	UART uart_;
	
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
		nyesteBit_ = nyestebit;
}

int RecieverLamp::readStartBits(){
	seneste6Bits_ = 0;
	counter_ = 0;
	while(startBits_ != seneste6Bits_){
			if (zeroCross_ == 1)
			{
				if (counter_ <= 6)
				{
				
				readADC();
				
				seneste6Bits_ = seneste6Bits_ << 1;
				seneste6Bits_ |= nyesteBit_; 
				//PORTB = seneste6Bits_;
			
				zeroCross_ = 0;
				// PORTB ^= (1<<6);		bruges til at teste
				counter_++;
				}
				else{
					return 0;
				}
			}
	}
	
	
	return 1;
	
}
int RecieverLamp::readAdresseBits(){
	seneste6Bits_ = 0;
	counter_ = 0;
	
	while(adresseBits_ != seneste6Bits_){
		if (zeroCross_ == 1)
		{
			if (counter_ <= 6){
			readADC();
			
			seneste6Bits_ = seneste6Bits_ << 1;
			seneste6Bits_ |= nyesteBit_;
			//PORTB = seneste6Bits_;
			
			zeroCross_ = 0;
			// PORTB ^= (1<<6);		bruges til at teste
			
			}else{
				return 0;
			}
		}
	}
	
	return 1;
	
}
int RecieverLamp::readDataBits(){
	seneste6Bits_ = 0;
	counter_ = 0;
	while(kommandoBits_ != seneste6Bits_){
		if (zeroCross_ == 1)
		{
			if (counter_ <= 6){}
			readADC();
			
			seneste6Bits_ = seneste6Bits_ << 1;
			seneste6Bits_ |= nyesteBit_;
			//PORTB = seneste6Bits_;
			
			zeroCross_ = 0;
			// PORTB ^= (1<<6);		bruges til at teste
			
			}else{
				return 0;
			}
	}
	
	return 1;
	
}
int RecieverLamp::readStopBits(){
	seneste6Bits_ = 0;
	counter_ = 0;
	while(stopBits_ != seneste6Bits_){
		if (zeroCross_ == 1)
		{
			if (counter_ <= 6){
			readADC();
			
			seneste6Bits_ = seneste6Bits_ << 1;
			seneste6Bits_ |= nyesteBit_;
			
			zeroCross_ = 0;
			}else{
				return 0;
			}
		}
	}
	
	return 1;
}

void RecieverLamp::readADC(){
	
	//// timer
	TCNT0 = 201;
	TCCR0A |= 0b00000000; // starter timer
	TCCR0B |= 0b00000101;
	while((TIFR0 & (1<<0)) == 0)
	{}
	TCCR0B = 0b00000000; // slut timer
	TIFR0 = 0b00000001;
	//// timer
	
	////ADC start
	ADCSRA |= 0b01000000;
			
	while (ADCSRA & 0b01000000)
	{}
	
	ADCread_ = ADCW;
	////ADC slut
	////sendet ud p� uart
	uart_->SendInteger(ADCread_);
	uart_->SendString("\\");
	
	////s�tter nyeste bit alt efter hvad adc giver af v�rdi
	if ((ADCread_ > ADClastRead_) && (ADCread_> 5))
	{
		nyesteBit_ = 1;			
	}								
	else
	{
		nyesteBit_ = 0; 
	}
	ADClastRead_ = ADCread_;
	
	uart_->SendInteger(nyesteBit_);
	uart_->SendString("\\");	
}

void RecieverLamp::turnOnLight()
{
	PORTB = 0b11111111;
}