/* 
* UART.cpp
*
* Created: 17-05-2022 10:08:16
* Author: Frederik
*/


#include "UART.h"

// default constructor
UART::UART()
{
	UCSR0B = 0b10011000;			// Tænder for sender og modtager + enabler interupt ved modtagelse
	UBRR0 = 103;					// Værdien gør at baud raten er 9600
	UCSR0C = 0b00000110;			// bit 0 gør ingenting
									// bit 1 og 2 "11" = 8 data bit
									// bit 3 "0" = 1 stopbit
									// bit 4 og 5 "00" = ingen paritets bit
									// bit 6 og 7 "00" = asynkron mode
									
} //UART

void UART::SendChar(char Tegn)
{
	// <---- Skriv din kode her
	while((0b00100000 & UCSR0A) == 0)
	{}
	UDR0 = Tegn;
}

void UART::SendString(char* Streng)
{
	while (*Streng != 0)
	{
		SendChar(*Streng);
		Streng++;
	}
}

void UART::SendInteger(int Tal)
{
	char array[7];
	// Convert the integer to an ASCII string (array), radix = 10
	itoa(Tal, array, 10);
	// - then send the string
	SendString(array);
}