/*
 * Reviever.cpp
 *
 * Created: 12-05-2022 08:19:58
 * Author : Frederik
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>



bool zerocross = false;		// Bliver True når der har været et ZeroCross
int nyesteBit = 0;			// Får en værdi inde i interupt
int laengde = 0;			// Bruges til at teste inde i interupt rutinen

ISR(INT0_vect);
void initInterupt0();

int main(void)
{
	DDRF = 0;
	DDRD = 0;			//Sætter IO pins kan tilføjes i en funktion
	DDRB = 0xFF;
	PORTB = 0;
	
	initInterupt0();
	
	int startbit = 0b1110;
	int slutbit = 0b0111;
	int seneste4Bit = 0b0010;
	int bit6, bit5, bit4, bit3, bit2, bit1;
	int moenster6, moenster5, moenster4, moenster3, moenster2 = 0b0000;
	int adresse = 0b000000;
	int kommando = 0b000000;
	
    /* Replace with your application code */
    while (1) 
    {
		
		while(startbit != seneste4Bit)
			if (zerocross)
			{
								
				moenster4 = bit3;
				moenster3 = bit2;
				moenster2 = bit1;
				bit1 = nyesteBit;
				
				seneste4Bit = moenster4 | moenster3 | moenster2 | bit1;
				
				zerocross = false;
				// PORTB ^= (1<<6);		bruges til at teste
				
				/*bit4 = bit3;
				bit3 = bit2;
				bit2 = bit1;
				bit1 = nyesteBit;
				
				moenster4 = (bit4 << 3);
				moenster3 = (bit3 << 2);
				moenster2 = (bit2 << 1);*/
			}
		
		int adresselaengde = 0;
		
		while (adresselaengde != 6)		// Aflæser de næste 6 zerocross og ligger dem i adresse
		{
			//PORTB ^= (1<<5);		Bruges til at teste
			if (zerocross)
			{
				bit6 = bit5;
				bit5 = bit4;
				bit4 = bit3;
				bit3 = bit2;
				bit2 = bit1;
				bit1 = nyesteBit;
				
				moenster6 = (bit6 << 5);
				moenster5 = (bit5 << 4);		
				moenster4 = (bit4 << 3);
				moenster3 = (bit3 << 2);
				moenster2 = (bit2 << 1);
						
				adresse = moenster6 | moenster5 | moenster4 | moenster3 | moenster2 | bit1;
						
				zerocross = false;
				adresselaengde++;
			}
			
		}
		
		int komandolaengde = 0;
		
		while (komandolaengde != 6)		// Aflæser de næste 6 zeroCross og ligger dem i kommando
		{
			// PORTB ^= (1<<4);		Bruges til at teste
			if (zerocross)
			{
				bit6 = bit5;
				bit5 = bit4;
				bit4 = bit3;
				bit3 = bit2;
				bit2 = bit1;
				bit1 = nyesteBit;
				
				moenster6 = (bit6 << 5);
				moenster5 = (bit5 << 4);
				moenster4 = (bit4 << 3);
				moenster3 = (bit3 << 2);
				moenster2 = (bit2 << 1);
				
				kommando = moenster6 | moenster5 | moenster4 | moenster3 | moenster2 | bit1;
				
				zerocross = false;
				komandolaengde++;
			}			
		}
		
		
		seneste4Bit = 0b0000;
		while(slutbit != seneste4Bit)		//Kigger efter stopbit
		{
			//PORTB ^= (1<<3);		Bruges til at teste
			if (zerocross)
			{
				bit4 = bit3;
				bit3 = bit2;
				bit2 = bit1;
				bit1 = nyesteBit;
			
				moenster4 = (bit4 << 3);
				moenster3 = (bit3 << 2);
				moenster2 = (bit2 << 1);
			
				seneste4Bit = moenster4 | moenster3 | moenster2 | bit1;
			
				zerocross = false;
				
			}
		}
		
		if (adresse == 0b010101)		// Skal ændres til nogle funktioner
		{
			switch(kommando)
			{
				case 0b101010:			// Denne kommando skal tænde LEDer
					PORTB = 0b00000111;
					_delay_ms(3000);
					break;
				case 0b010101:			// Denne kommando skal slukke LEDer
					PORTB = 0;
					_delay_ms(3000);
					break;
				default:				// Default gør ingenting
					break;
			}
		}
		_delay_ms(2000);				// Viser adressen og kommando på LEDer
		PORTB = adresse;				//
		_delay_ms(2000);				//
		PORTB = kommando;				//
		
    }
}


ISR(INT0_vect)
{
	//if (PINF0 > 15)
	//{
		//nyesteBit = 1;
	//}								Dette er ikke testet, men virker måske
	//else
	//{
		//nyesteBit = 0;
	//}
	
	switch(laengde)				// Switchen bliver brugt til at teste
	{
	case 0:
		nyesteBit = 1;
		break;
	case 1:
	nyesteBit = 1;
	break;	
	case 2:
	nyesteBit = 1;
	break;	
	case 3:
	nyesteBit = 0;
	break;
	case 4:
	nyesteBit = 0;
	break;
	case 5:
	nyesteBit = 1;
	break;
	case 6:
	nyesteBit = 0;
	break;
	case 7:
	nyesteBit = 1;
	break;
	case 8:
	nyesteBit = 0;
	break;
	case 9:
	nyesteBit = 1;
	break;
	case 10:
	nyesteBit = 1;
	break;
	case 11:
	nyesteBit = 0;
	break;
	case 12:
	nyesteBit = 1;
	break;
	case 13:
	nyesteBit = 0;
	break;
	case 14:
	nyesteBit = 1;
	break;
	case 15:
	nyesteBit = 0;
	break;
	case 16:
	nyesteBit = 1;
	break;
	case 17:
	nyesteBit = 0;
	break;
	case 18:
	nyesteBit = 1;
	break;
	case 19:
	nyesteBit = 1;
	break;
	}
	laengde++;
	PORTB ^= (1<<7);
	
	zerocross = true;			// Bliver sat true hver gang der har været et cross
}

void initInterupt0()				// Int0 Gøres klar
{
	sei();
	EIMSK |= 0b00000001;
	EICRA |= 0b00000001;
	
}