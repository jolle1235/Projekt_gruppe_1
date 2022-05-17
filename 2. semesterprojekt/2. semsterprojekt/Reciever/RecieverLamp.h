/* 
* Reciever.h
*
* Created: 17-05-2022 12:57:08
* Author: jespe
*/


#ifndef __RECIEVER_H__
#define __RECIEVER_H__


class RecieverLamp
{
public:
	RecieverLamp();
	~RecieverLamp();
	int getZeroCross();
	void setZeroCross(int zeroCross);
	int getNyesteBit();
	void setNyesteBit(int nyestebit);
	int readStartBits();
	int readAdresseBits();
	int readDataBits();
	int readStopBits();
	void readADC();
	void turnOnLight();
	
private:
	int zeroCross_;
	int nyesteBit_;
	int seneste6Bits_;
	int startBits_;
	int stopBits_;
	int adresseBits_;
	int kommandoBits_;	
	int x;
	UART* uart_;
	RecieverLamp( const RecieverLamp &c );
	RecieverLamp& operator=( const RecieverLamp &c );

}; //RecieverLamp


#endif //__RECIEVER_H__
