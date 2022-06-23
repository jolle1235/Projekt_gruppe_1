/*
 * Reviever.cpp
 *
 * Created: 12-05-2022 08:19:58
 * Author : Frederik
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "UART.h"
#include "Reciever.h"


	
ISR(INT0_vect);
void initInterupt0();
void initADC();
Reciever Reciever;
UART uart_;

void initInterupt0()				// Int0 Gøres klar
{
	sei();
	EIMSK |= 0b00000001;
	EICRA |= 0b00000001;
	
}

void initADC()						// ADC bliver klar gjordt
{
	ADCSRA = 0b10000111;
	ADMUX = 0b01000000;
	ADCSRB = 0b00000000;
	
}

int main(void)
{
	UART uart;
	
	DDRF = 0;
	DDRD = 0;			//Sætter IO pins kan tilføjes i en funktion
	DDRB = 0xFF;
	PORTB = 0;
	int adresse;
	int data;
	initInterupt0();
	initADC();
	
	Reciever.setAdresseBits();
	
	uart.SendInteger(Reciever.getAdresseBits());
	uart.SendString("\n\r");
	
	
	uart.SendString("program starter \n");
	
    /* Replace with your application code */
    while (1) 
    {
		if (Reciever.readStartBits() == 1)
		{
			adresse = Reciever.readAdresseBits();
			data = Reciever.readDataBits();
			Reciever.readStopBits();
			
			if (adresse == Reciever.getAdresseBits())
			{
				uart.SendString("\n\rAdressen passede");
				switch(data)
				{
					case 42:											//svare til 101010
						Reciever.turnOnLight();
						break;
					case 21:											//svare til 010101
						Reciever.turnOffLight();
						break;
					default:
						uart.SendString("Den gik i default\n\r");
						break;
				}
			}
			
	
		}
		data = 0;
		adresse = 0;
		
	}
}


ISR(INT0_vect)
{
	
	Reciever.setZeroCross(1);			// Bliver sat true hver gang der har været et cross
	
}
