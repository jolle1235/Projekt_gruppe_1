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
	int adresse[6];
	int kommando[6];
	
	uart0.SendString("Program startet.\f\n\n\n\r");
	uart0.SendString("____________________________________________\n\r");
	uart0.SendString("      X         X         X                X X X X\n\r");
	uart0.SendString("     X X        X         X                      X\n\r");
	uart0.SendString("    X   X       X         X                      X  \n\r");
	uart0.SendString("   X     X      X         X    X X X X X   X X X X\n\r");
	uart0.SendString("  X X X X X     X         X                X\n\r");
	uart0.SendString(" X         X     X       X                 X\n\r");
	uart0.SendString("X           X     X X X X                  X X X X \n\r");
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
			
			
			if ((modtaget == '1') || (modtaget == 'b') || (modtaget == 'c') || (modtaget == 'd'))
			{
				switch (modtaget)
				{
				case '1':
					uart0.SendString("\n\rLampen taendes.");
					adresse[0] = 0;
					adresse[1] = 1;
					adresse[2] = 0;
					adresse[3] = 1;
					adresse[4] = 0;
					adresse[5] = 1;
					sender.setAdresse(adresse);
					kommando[0] = 1;
					kommando[1] = 0;
					kommando[2] = 1;
					kommando[3] = 0;
					kommando[4] = 1;
					kommando[5] = 0;
					break;
				case 'b':
					uart0.SendString("Lampen slukkes");
					break;
				}
				
				sender.setZeroCross(0);
				sender.sendStartBits();
				
				sender.sendAdresseBits(adresse);
				
				sender.sendKommandoBits(kommando);

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