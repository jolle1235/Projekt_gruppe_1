/*
 * TransmitterTV.cpp
 *
 * Created: 25-05-2022 11:51:20
 * Author : jespe
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "UART.h"
#include "TransmitterTV.h"


ISR(INT0_vect);
volatile TransmitterTV TV;
initInterupt0();
initIOpins();


int main(void)
{
	
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}


ISR(INT0_vect){
	TV.setZeroCross(1);
	TV.startDelay();
		
}

ISR(TIMER1_OVF_vect){
	TV.stopDelay();
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

