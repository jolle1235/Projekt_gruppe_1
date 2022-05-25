/* 
* TransmitterTV.h
*
* Created: 25-05-2022 11:51:42
* Author: jespe
*/


#ifndef __TRANSMITTER_H__
#define __TRANSMITTER_H__
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "UART.h"


class TransmitterTV
{
//functions
public:
	TransmitterTV();
	~TransmitterTV();
	int getZeroCross();
	void setZeroCross(int zeroCross);
	void sendStartBits();
	void sendKommandoBits();
	void sendStopBits();
	void startDelay();
	void stopDelay();
	int checkIfTurnedOn();

//variables
private:
	int zeroCross_;
	int startBits_[];
	int KommandoBits_[];
	int stopBits_[];
	int TVstatus_;
	
	TransmitterTV( const TransmitterTV &c );
	TransmitterTV& operator=( const TransmitterTV &c );
	
}; //TransmitterTV

#endif //__TRANSMITTERTV_H__
