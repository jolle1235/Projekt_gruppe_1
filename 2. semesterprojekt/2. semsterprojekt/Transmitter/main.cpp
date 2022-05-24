/*
 * Transmitter.cpp
 *
 * Created: 16-05-2022 12:01:15
 * Author : Frederik
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "UART.h"
#include "Transmitter.h"

ISR(INT0_vect);
ISR(USART0_RX_vect);
void initInterupt0();
void initIOpins();


//volatile int zeroCross = 0;
volatile char modtaget;
Transmitter sender;

int main(void)
{
	initIOpins();
	initInterupt0();
	UART uart0;
	
	uart0.SendString("Program startet.\f\n\n\n\r");
	uart0.SendString("____________________________________________\n\r");
	uart0.SendString("    X        X       X                  X X X\n\r");
	uart0.SendString("   X X       X       X                      X\n\r");
	uart0.SendString("  X X X      X       X    X X X X X X   X X X \n\r");
	uart0.SendString(" X     X      X     X                   X     \n\r");
	uart0.SendString("X       X      X X X                    X X X  \n\r");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	uart0.SendString("");
	
	
    /* Replace with your application code */
    while (1) 
    {
			
			
			if ((modtaget == '1') || (modtaget == '2') || (modtaget == '3') || (modtaget == '4'))
			{
				switch (modtaget)
				{
				case '1':
				{
					uart0.SendString("\n\rLampen taendes.");
					int adresse[6] = {0,1,0,1,0,1};
					sender.setAdresse(adresse);
					int kommando[6] = {1,0,1,0,1,0};
					sender.setKommando(kommando);
				}
					break;
					
				case '2':
				{
					uart0.SendString("Lampen slukkes");
					int adresse[6] = {0,1,0,1,0,1};
					sender.setAdresse(adresse);
					int kommando[6] = {0,1,0,1,0,1};
					sender.setKommando(kommando);	
				}
					break;
				case '3':
				{
					uart0.SendString("Gardin rulles op");
					int adresse[6] = {1,0,1,0,1,0};
					sender.setAdresse(adresse);
					int kommando[6] = {1,0,1,0,1,0};
					sender.setKommando(kommando);
				}
				break;
				case '4':
				{
					uart0.SendString("Gardin rulles ned");
					int adresse[6] = {1,0,1,0,1,0};
					sender.setAdresse(adresse);
					int kommando[6] = {0,1,0,1,0,1};
					sender.setKommando(kommando);
				}
				break;
				default:
					break;
				}
				
				sender.setZeroCross(0);
				sender.sendStartBits();
				
				sender.sendAdresseBits();
				
				sender.sendKommandoBits();

				sender.sendStopBits();
						
				PORTB = PINB ^ 0b11111111;

			}
		modtaget = '0';
		
    }
}

ISR(INT0_vect)
{
	sender.setZeroCross(1);
	PORTB = PINB ^ 0b10000000;
}

ISR(USART0_RX_vect)
{
	modtaget = UDR0;
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