/*
 * acoustic-location.cpp
 *
 * Created: 2/11/2020 5:17:04 PM
 * Author : Team 5
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include <string.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init( unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned int data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

int main(void) {
	
/* USART Setup */
USART_Init(MYUBRR);

/* Set all pins on PORTL to input mode.
 *  Arduino pins 42, 43, 48, and 49 all belong
 *  to this port as found on the data sheet.
 */
DDRL |= 0;

/* Set LED pin to output mode */
DDRB |= 10000000;

/* Timer 1 setup */
TIFR1 = (1<<ICF1);    // Clear pending interrupts and Overflow Flag Interrupt
TCCR1A = 0;           // Disable compare interrupts (necessary for arduino) and set WGM to normal mode
TCCR1B = (0<<ICNC1)|  // Turn off noise filtering
(1<<ICES1)|           // Set input capture edge to rising
(0<<WGM13)|           // Set WGM to normal
(0<<WGM12)|
(1<<CS11)|            // CS bits set pre-scale to /64
(1<<CS10);
TIMSK1 = (1<<ICIE1)|  // Enable 16-bit Timer Capture Event Interrupt
(0<<TOIE1);           // Disable Overflow Interrupt

/* Timer 3 setup */
TIFR3 = (1<<ICF3);
TCCR3A = 0;
TCCR3B = (0<<ICNC3)|(1<<ICES3)|(0<<WGM33)|(0<<WGM32)|(1<<CS31)|(1<<CS30);
TIMSK1 = (1<<ICIE3)|(0<<TOIE3);

/* Timer 4 setup */
TIFR4 = (1<<ICF4);
TCCR4A = 0;
TCCR4B = (0<<ICNC4)|(1<<ICES4)|(0<<WGM43)|(0<<WGM42)|(1<<CS41)|(1<<CS40);
TIMSK4 = (1<<ICIE4)|(0<<TOIE4);

/* Timer 5 setup */
TIFR5 = (1<<ICF5);
TCCR5A = 0;
TCCR5B = (0<<ICNC5)|(1<<ICES5)|(0<<WGM53)|(0<<WGM52)|(1<<CS51)|(1<<CS50);
TIMSK5 = (1<<ICIE5)|(0<<TOIE5);

/* Enable global interrupts */
sei();
	while(1) {
		/* Turn of LED */
		PORTB &= ~0x80;
		
		/* Reset timers */
		TCNT1 = 0;
		TCNT3 = 0;
		TCNT4 = 0;
		TCNT5 = 0;

		/* Check PORTL pins 0, 1, 6, and 7 for HIGH value */
		if (PINL & 0b11000011) {
			/* Disable global interrupts, and restore sreg state upon exit */
			ATOMIC_BLOCK(ATOMIC_FORCEON) {
				/* The max difference in tics will equal: (max_dist / speed_of_sound) * tics_per_sec
				*  With a clock of of 250kHz each tick is 1/4 of a micro second, so multiply by 4 to
				*  get real time in micro seconds.
				*/
				
				/* Transmit ICRs */
				USART_Transmit(ICR1);
				USART_Transmit(ICR3);
				USART_Transmit(ICR4);
				USART_Transmit(ICR5);
				
				/* Transmit timer overflow flags */
				USART_Transmit(TOV1);
				USART_Transmit(TOV3);
				USART_Transmit(TOV4);
				USART_Transmit(TOV5);
				USART_Transmit(10);

				/* Clear pending interrupts before restoring global interrupts so we don't
				*  immediately trigger the check loop again.
				*/
				TIFR1 = (1<<ICF1);
				TIFR3 = (1<<ICF3);
				TIFR4 = (1<<ICF4);
				TIFR5 = (1<<ICF5);
			}
			/* Turn on LED */
			PORTB |= 0x80;
			
			/* Delay for remaining length of high signal */
			_delay_ms(520);
		}
	}
}
