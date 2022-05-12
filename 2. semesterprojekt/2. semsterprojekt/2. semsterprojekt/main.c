/*
 * 2. semsterprojekt.c
 *
 * Created: 28-04-2022 12:19:15
 * Author : jespe
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>



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
	
}

