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


volatile char modtaget;
Transmitter sender;

int main(void)
{
	initIOpins();
	initInterupt0();
	UART uart0;
	
	uart0.SendString("Program startet.\f\n\n\n\r");
	uart0.SendString("_________________________________________________  \n\n\r");
	uart0.SendString("    X         X       X                  X X X X   \n\r");
	uart0.SendString("   X X        X       X                        X   \n\r");
	uart0.SendString("  X   X       X       X    X X X X X     X X X X   \n\r");
	uart0.SendString(" X X X X       X     X                   X         \n\r");
	uart0.SendString("X       X       X X X                    X X X X   \n\n\n\r");
	uart0.SendString("");
	uart0.SendString("X       X      X X X      X        X      X X X X  \n\r");
	uart0.SendString("X       X     X     X     X X    X X      X        \n\r");
	uart0.SendString("X X X X X    X       X    X  X  X  X      X X X    \n\r");
	uart0.SendString("X       X     X     X     X   XX   X      X        \n\r");
	uart0.SendString("X       X      X X X      X        X      X X X X  \n\r");
	uart0.SendString("__________________________________________________ \n\n\r");
	uart0.SendString("Taend lys:      Tast '1'                           \n\r");
	uart0.SendString("Sluk lys:       Tast '2'                           \n\r");
	uart0.SendString("Rul gardin op:  Tast '3'                           \n\r");
	uart0.SendString("Rul gardin ned: Tast '4'                           \n\r");
	uart0.SendString("Sluk Hjem:      Tast '5'                           \n\r");
	uart0.SendString("__________________________________________________ \n\r");	
	
    /* Replace with your application code */
    while (1) 
    {
			
			
			if ((modtaget == '1') || (modtaget == '2') || (modtaget == '3') || (modtaget == '4') || (modtaget == '5'))	// Program reagerer kun hvis den modtager char 1-5 
			{
				switch (modtaget)
				{
				case '1':		// Tænder lampen
				{
					uart0.SendString("Lampen taendes.\n\r");
					int adresse[6] = {0,1,0,1,0,1};
					sender.setAdresse(adresse);
					int kommando[6] = {1,0,1,0,1,0};
					sender.setKommando(kommando);
				}
					break;
					
				case '2':		// Slukker lampen
				{
					uart0.SendString("Lampen slukkes\n\r");
					int adresse[6] = {0,1,0,1,0,1};
					sender.setAdresse(adresse);
					int kommando[6] = {0,1,0,1,0,1};
					sender.setKommando(kommando);	
				}
					break;
				case '3':		// Gardin rulles op
				{
					uart0.SendString("Gardin rulles op\n\r");
					int adresse[6] = {1,0,0,1,1,0};
					sender.setAdresse(adresse);
					int kommando[6] = {1,0,1,0,1,0};
					sender.setKommando(kommando);
				}
				break;
				case '4':		// Gardin rulles ned
				{
					uart0.SendString("Gardin rulles ned\n\r");
					int adresse[6] = {1,0,0,1,1,0};
					sender.setAdresse(adresse);
					int kommando[6] = {0,1,0,1,0,1};
					sender.setKommando(kommando);
				}
				break;
				case '5':		// Slukker hjem
				{
					uart0.SendString("Hjem lukkes ned\n\r");
					int adresse[6] = {1,0,0,1,1,0};
					sender.setAdresse(adresse);
					int kommando[6] = {0,1,0,1,0,1};
					sender.setKommando(kommando);
				}				
				default:
					break;
				}
				
				
				sender.setZeroCross(0);
				
				sender.sendStartBits();
				sender.sendAdresseBits();
				sender.sendKommandoBits();
				sender.sendStopBits();
				
				if (modtaget == '5')
				{
					sender.setZeroCross(0);
					
					int adresse[6] = {0,1,0,1,0,1};
					sender.setAdresse(adresse);
					sender.sendStartBits();									
					sender.sendAdresseBits();									
					sender.sendKommandoBits();
					sender.sendStopBits();
				}
						
				PORTB = PINB ^ 0b11111111;		// Toggler port B når transmitteren er færdig med at sende

			}
		modtaget = '0';			// Nulstiller modtager så den ikke udfører en kommando igen
		
    }
}

ISR(INT0_vect)
{
	sender.setZeroCross(1);			// Sætter zeroCross_ til 1
}

ISR(USART0_RX_vect)
{
	modtaget = UDR0;			// Den værdi UARTen modtager bliver gemt i modtaget
}

void initInterupt0()
{
	sei();					// Enable global interupt
	EIMSK |= 0b00000001;	// Enabler interupt 0
	EICRA |= 0b00000001;	// Enabler interupt 1 ved falling og rising edge
}

void initIOpins()
{
		DDRB = 0xFF;		// Udgang
		DDRC = 0xFF;		// Udgang
		DDRD = 0;			// Indgang
		PORTB = 0;			// Nulstiller PortB
		PORTC = 0;			// Nulstiller PortC
		PORTD = 0;			// Nulstiller PortD
}