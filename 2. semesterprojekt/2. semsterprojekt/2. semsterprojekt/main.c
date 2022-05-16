/*
 * 2. semsterprojekt.c
 *
 * Created: 28-04-2022 12:19:15
 * Author : jespe
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

bool zeroCross = false;


int main(void)
{
	sei();
	DDRB = 0b11111111;
	
	initIOpins();
	initINT0();
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

ISR(INT0_vect)
{
	turnOnLight();
	zeroCross = true;
}

/*
char reccivedChar;

([default kommandoer])
bool light;            //lys kan være tændt eller slukket



hvis reccivedChar == "1" 
{
	sæt en addrasse;
	derefter send end komando; 
}

if char pressed == "T"
	turn on light
	if light is one
		turn off light
	
	
=====================
indkodning
[10] = 1
[01] = 0

[1110]   start
[010101] adresse på mikrokontroler 
[######] data
[0111]   slut


=================

//globale variable
bool ZeroCross = false;

void sendStartBit(void)
{
	int bitArray[4];
	for(int i = 0; i < 4; i++)
	{
		while(ZeroCross == 0)
		{}
	ZeroCross = false;
	portc = bitArray[i];
	}
}


======

//globale variable
bool ZeroCross = false;

void sendSlutBit(void)
{
	int bitArray[4];
	for(int i = 0; i < 4; i++)
	{
		while(ZeroCross == 0)
		{}
		ZeroCross = false;
		portc = bitArray[i];
	}
}


=======

//globale variable
bool ZeroCross = false;

void sendAddrasseBit(int intArray[])
{
	for(int i = 0; i < 6; i++)
	{
		while(ZeroCross == 0)
		{}
		ZeroCross = false;
		portc = intArray[i];
	}
}



=======
void sendDataBit(int intArray[])
{
	for(int i = 0; i < 6; i++)
	{
		while(ZeroCross == 0)
		{}
		ZeroCross = false;
		portc = intArray[i];
	}
}
  
                       (10 01 10)     (1 0 1)-->komanda     (udførlse af komando)
[mikro controler]---(sender data)--->[mikro controler 2]----(står for at togle)---->[lys]
*/

