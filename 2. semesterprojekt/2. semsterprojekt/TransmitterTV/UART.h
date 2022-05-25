/* 
* UART.h
*
* Created: 17-05-2022 10:08:16
* Author: Frederik
*/


#ifndef __UART_H__
#define __UART_H__
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>





class UART
{
//variables
private:

//functions
public:
	UART();
	void SendChar(char Tegn);
	void SendString(char* Streng);


}; //UART

#endif //__UART_H__
