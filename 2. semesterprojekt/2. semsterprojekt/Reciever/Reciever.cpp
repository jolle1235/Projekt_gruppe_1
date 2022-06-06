/* 
* Reciever.cpp
*
* Created: 17-05-2022 12:57:08
* Author: jespe
*/


#include "Reciever.h"


// default constructor
Reciever::Reciever()
{
	zeroCross_ = 0;
	nyesteBit_ = 0;
	ADCread_ = 0;
	ADClastRead_ = 0;
	seneste6Bits_ = 0b000000;
	startBits_ = 0b1110;
	stopBits_ = 0b0111;
	adresseBits_ = 0b010101; // 111 / 000 binær
	kommandoBits_ = 0b101010; //
	UART uart_;
	
} 

// default destructor
Reciever::~Reciever()
{
	
} 
int Reciever::getZeroCross()
{
	return zeroCross_;
}
void Reciever::setZeroCross(int zeroCross)
{
	zeroCross_ = zeroCross;
}

int Reciever::getNyesteBit()
{
		return nyesteBit_;		
}
void Reciever::setNyesteBit(int nyestebit)
{
		nyesteBit_ = nyestebit;
}

int Reciever::readStartBits(){
	seneste6Bits_ = 0;
	counter_ = 0;
	while(startBits_ != seneste6Bits_){
			if (zeroCross_ == 1)
			{
		
				
				readADC();
				
				seneste6Bits_ = seneste6Bits_ << 1;
				seneste6Bits_ |= nyesteBit_; 
				//PORTB = seneste6Bits_;
			
				zeroCross_ = 0;
				// PORTB ^= (1<<6);		bruges til at teste

	
			}
	}
	
	
	return 1;
	
}
int Reciever::readAdresseBits(){
	seneste6Bits_ = 0;
	counter_ = 0;
	
	while(adresseBits_ != seneste6Bits_){
		if (zeroCross_ == 1)
		{
			if (counter_ < 6){
			readADC();
			
			seneste6Bits_ = seneste6Bits_ << 1;
			seneste6Bits_ |= nyesteBit_;
			
			zeroCross_ = 0;
			counter_++;
			}
			else
			{
				return seneste6Bits_;
			}
		}
	}
	
	return seneste6Bits_;
	
}
void Reciever::setAdresseBits()
{
	while (PINA & 0b01000000)
	{
		if ((PINA & 0b00000001) == 0)
		{
			_delay_ms(250);
			PORTB = PINB ^ 0b00000001;
		}
		if ((PINA & 0b00000010) == 0)
		{
			_delay_ms(250);
			PORTB = PINB ^ 0b00000010;
		}
		if ((PINA & 0b00000100) == 0)
		{
			_delay_ms(250);
			PORTB = PINB ^ 0b00000100;
		}
		if ((PINA & 0b00001000) == 0)
		{
			_delay_ms(250);
			PORTB = PINB ^ 0b00001000;
		}
		if ((PINA & 0b00010000) == 0)
		{
			_delay_ms(250);
			PORTB = PINB ^ 0b00010000;
		}
		if ((PINA & 0b00100000) == 0)
		{
			_delay_ms(250);
			PORTB = PINB ^ 0b00100000;
		}
	}
		adresseBits_ = PINB;
		PORTB |= 0b01000000;
}
int Reciever::getAdresseBits()
{
	return adresseBits_;
}

int Reciever::readDataBits()
{
	seneste6Bits_ = 0;
	counter_ = 0;
	
	while(kommandoBits_ != seneste6Bits_)      // Går ud fra at denne lykke vare 6bit, altså det er lykken som hvor afkoden sker.
	{				
		if (zeroCross_ == 1)
		{
			if (counter_ < 6)
			{
			readADC();
			
			seneste6Bits_ = seneste6Bits_ << 1;
			seneste6Bits_ |= nyesteBit_;
			
			zeroCross_ = 0;
			counter_++;
			}
			else
			{
				return seneste6Bits_;
			}
		}
	}
	
	return seneste6Bits_;
	


}
/*
ABSTRACT:
koden oven over, skal aflæse havd der bliver modtaget (indkodet analog og ikke binært signal)signal 
og så skal den retuner en int som er et afkodet kommando.
*/ 
int Reciever::readStopBits()
{
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

void Reciever::readADC(){
	
	//// timer
	TCNT0 = 240;			// timer på 1 ms	
	TCCR0A |= 0b00000000;	// starter timer
	TCCR0B |= 0b00000101;	// Prescale på 1024
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
	////sendet ud på uart
	uart_->SendInteger(ADCread_);
	uart_->SendString("\\");
	

	////sætter nyeste bit alt efter hvad adc giver af værdi
	if (((ADCread_ > ADClastRead_) && (ADCread_> 10)) || (ADCread_ > 50))
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

void Reciever::turnOnLight()
{
	PORTB = 0xFF;
}

void Reciever::turnOffLight()
{
	PORTB = 0;	
}
