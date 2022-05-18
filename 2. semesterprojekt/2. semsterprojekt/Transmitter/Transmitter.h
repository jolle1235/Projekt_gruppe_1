/* 
* Transmitter.h
*
* Created: 17-05-2022 12:14:39
* Author: Frederik
*/


#ifndef __TRANSMITTER_H__
#define __TRANSMITTER_H__
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "UART.h"

//volatile int zeroCross = 0;
//volatile int startbit[4] = {1,1,1,0};

class Transmitter
{
//variables
private:
	int zeroCross;
	static int startbit[4];
	static int stopbit[4];
	int adresse[6];
//functions
public:
	Transmitter();
	int getZeroCross();
	void setZeroCross(int x);
	void setAdresse(int array[]);
	void sendStartBits();
	void sendAdresseBits(int array[]);
	void sendKommandoBits(int array[]);
	void sendStopBits();

}; //Transmitter

#endif //__TRANSMITTER_H__
