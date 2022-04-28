/*
 * 2. semsterprojekt.c
 *
 * Created: 28-04-2022 12:19:15
 * Author : jespe
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB = 1;
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0b01101110;
    }
}

