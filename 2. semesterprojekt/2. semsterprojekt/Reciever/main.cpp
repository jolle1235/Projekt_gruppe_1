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
#include "RecieverLamp.h"


	
ISR(INT0_vect);
void initInterupt0();
void initADC();

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
	RecieverLamp Reciever;
	DDRF = 0;
	DDRD = 0;			//Sætter IO pins kan tilføjes i en funktion
	DDRB = 0xFF;
	PORTB = 0;
	int x;
	initInterupt0();
	initADC();
	
	
	
	uart.SendString("program starter \n");
	
    /* Replace with your application code */
    while (1) 
    {
		if (Reciever.readStartBits() == 1)
		{
			if (Reciever.readAdresseBits() == 1)
			{
				if (Reciever.readDataBits() == 1)
				{
					if (Reciever.readStopBits() == 1)
					{
						Reciever.turnOnLight();
					}
				}
			}
		}		
	}
}


ISR(INT0_vect)
{
	UART uart;
	RecieverLamp Reciever;
	PORTB = PINB ^ 0b10000000;
	
	Reciever.setZeroCross(1);			// Bliver sat true hver gang der har været et cross
	
	
}


//while (adresselaengde != 6)		// Aflæser de næste 6 zerocross og ligger dem i adresse
//{
	////PORTB ^= (1<<5);		Bruges til at teste
	//if (zerocross)
	//{
		//bit6 = bit5;
		//bit5 = bit4;
		//bit4 = bit3;
		//bit3 = bit2;
		//bit2 = bit1;
		//bit1 = nyesteBit;
		//
		//moenster6 = (bit6 << 5);
		//moenster5 = (bit5 << 4);
		//moenster4 = (bit4 << 3);
		//moenster3 = (bit3 << 2);
		//moenster2 = (bit2 << 1);
		//
		//adresse = moenster6 | moenster5 | moenster4 | moenster3 | moenster2 | bit1;
		//
		//zerocross = false;
		//adresselaengde++;
	//}
	//
//}
//
//int komandolaengde = 0;
//
//while (komandolaengde != 6)		// Aflæser de næste 6 zeroCross og ligger dem i kommando
//{
	//// PORTB ^= (1<<4);		Bruges til at teste
	//if (zerocross)
	//{
		//bit6 = bit5;
		//bit5 = bit4;
		//bit4 = bit3;
		//bit3 = bit2;
		//bit2 = bit1;
		//bit1 = nyesteBit;
		//
		//moenster6 = (bit6 << 5);
		//moenster5 = (bit5 << 4);
		//moenster4 = (bit4 << 3);
		//moenster3 = (bit3 << 2);
		//moenster2 = (bit2 << 1);
		//
		//kommando = moenster6 | moenster5 | moenster4 | moenster3 | moenster2 | bit1;
		//
		//zerocross = false;
		//komandolaengde++;
	//}
//}
//
//
//seneste4Bit = 0b0000;
//while(slutbit != seneste4Bit)		//Kigger efter stopbit
//{
	////PORTB ^= (1<<3);		Bruges til at teste
	//if (zerocross)
	//{
		//bit4 = bit3;
		//bit3 = bit2;
		//bit2 = bit1;
		//bit1 = nyesteBit;
		//
		//moenster4 = (bit4 << 3);
		//moenster3 = (bit3 << 2);
		//moenster2 = (bit2 << 1);
		//
		//seneste4Bit = moenster4 | moenster3 | moenster2 | bit1;
		//
		//zerocross = false;
		//
	//}
//}
//
//if (adresse == 0b010101)		// Skal ændres til nogle funktioner
//{
	//switch(kommando)
	//{
		//case 0b101010:			// Denne kommando skal tænde LEDer
		//PORTB = 0b00000111;
		//_delay_ms(3000);
		//break;
		//case 0b010101:			// Denne kommando skal slukke LEDer
		//PORTB = 0;
		//_delay_ms(3000);
		//break;
		//default:				// Default gør ingenting
		//break;
	//}
//}
//_delay_ms(2000);				// Viser adressen og kommando på LEDer
//PORTB = adresse;				//
//_delay_ms(2000);				//
//PORTB = kommando;				//
//
//}