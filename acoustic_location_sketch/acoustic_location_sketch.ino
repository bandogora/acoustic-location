#include <avr/interrupt.h>
#include <util/atomic.h>

/* Define microphone input signal pins */
#define ICPpin1 43  // ICP1 - ATmega2560 pin 47
#define ICPpin3 42  // ICP3 - ATmega2569 pin 9
#define ICPpin4 49  // ICP4 - ATmega2560 pin 35
#define ICPpin5 48  // ICP5 - ATmega2560 pin 36

void setup() {
  Serial.begin(9600, SERIAL_8O1);
  delay(500);

  /* Set all pins on PORTL to input mode.
      Arduino pins 42, 43, 48, and 49 all belong
      to this port as found on the data sheet.
  */
  DDRL |= 0;

  /* Timer 1 setup */
  TIFR1 = (1 << ICF1);  // Clear pending interupts and Overflow Flag Interrupt
  TCCR1A = 0;           // Disable compare interrupts (necessary for arduino) and set WGM to normal mode
  TCCR1B = (0 << ICNC1) | // Turn off noise filtering
           (1 << ICES1) |        // Set input capture edge to rising
           (0 << WGM13) |        // Set WGM to normal
           (0 << WGM12) |
           (1 << CS11) |         // CS bits set prescale to /64
           (1 << CS10);
  TIMSK1 = (1 << ICIE1) | // Enable 16-bit Timer Capture Event Interrupt
           (0 << TOIE1);         // Disable Overflow Interrupt
  TIFR1 = (1 << TOV1);  // Clear timer overflow flag

  /* Timer 3 setup */
  TIFR3 = (1 << ICF3);
  TCCR3A = 0;
  TCCR3B = (0 << ICNC3) |
           (1 << ICES3) |
           (0 << WGM33) |
           (0 << WGM32) |
           (1 << CS31) |
           (1 << CS30);
  TIMSK1 = (1 << ICIE3) |
           (0 << TOIE3);
  TIFR3 = (1 << TOV3);

  /* Timer 4 setup */
  TIFR4 = (1 << ICF4);
  TCCR4A = 0;
  TCCR4B = (0 << ICNC4) |
           (1 << ICES4) |
           (0 << WGM43) |
           (0 << WGM42) |
           (1 << CS41) |
           (1 << CS40);
  TIMSK4 = (1 << ICIE4) |
           (0 << TOIE4);
  TIFR4 = (1 << TOV4);

  /* Timer 5 setup */
  TIFR5 = (1 << ICF5);
  TCCR5A = 0;
  TCCR5B = (0 << ICNC5) |
           (1 << ICES5) |
           (0 << WGM53) |
           (0 << WGM52) |
           (1 << CS51) |
           (1 << CS50);
  TIMSK5 = (1 << ICIE5) |
           (0 << TOIE5);
  TIFR5 = (1 << TOV5);

  /* Enable global interrupts */
  sei();
}

void loop() {
  while (1) {
    /* Reset timers */
    TCNT1 = 0;
    TCNT3 = 0;
    TCNT4 = 0;
    TCNT5 = 0;

    /* Check PORTL pins 0, 1, 6, and 7 for HIGH value */
    if (PINL & 0b11000011) {
      /* Disable global interrupts, and restore sreg state upon exit */
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (ICR4 < 10 && ICR5 >= 10  && ICR3 >= 10){
          Serial.println((34) + (unsigned int)ICR1 * 1);
          Serial.println('-');
          Serial.println((34) + (unsigned int)ICR3 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR4 * 1);
          Serial.println('-');
          Serial.println((34) + (unsigned int)ICR5 * 1);
          Serial.println('+');
        }
        else if (ICR5 < 10 && ICR4 >= 10 && ICR1 >= 10){
          Serial.println(34 + (unsigned int)ICR1 * 1);
          Serial.println('-');
          Serial.println(34 + (unsigned int)ICR3 * 1);
          Serial.println('-');
          Serial.println(34 + (unsigned int)ICR4 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR5 * 1);
          Serial.println('+');
        }
        else if (ICR1 < 10 && ICR5 >= 10 && ICR3 >= 10){
          Serial.println((unsigned int)ICR1 * 1);
          Serial.println('-');
          Serial.println(34 + (unsigned int)ICR3 * 1);
          Serial.println('-');
          Serial.println(34 + (unsigned int)ICR4 * 1);
          Serial.println('-');
          Serial.println(34 + (unsigned int)ICR5 * 1);
          Serial.println('+');
        }
        else if (ICR3 < 10 && ICR1 >= 10 && ICR4 >= 10){
          Serial.println((unsigned int)ICR1 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR3 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR4 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR5 * 1);
          Serial.println('+');
        }
        else if ((ICR4 < 10 && ICR5 < 10) || (ICR5 < 10 && ICR4 < 10) && (ICR1 > 100) && (ICR3 > 100) ) {
          Serial.println(67 + (unsigned int)ICR1 * 1);
          Serial.println('-');
          Serial.println(67 + (unsigned int)ICR3 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR4 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR5 * 1);
          Serial.println('+');
        }
        else if ((ICR5 < 10 && ICR1 < 10) || (ICR5 < 10 && ICR1 < 10)  && (ICR4 > 100) && (ICR3 > 100)){
          Serial.println((unsigned int)ICR1 * 1);
          Serial.println('-');
          Serial.println(67 + (unsigned int)ICR3 * 1);
          Serial.println('-');
          Serial.println(67 +(unsigned int)ICR4 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR5 * 1);
          Serial.println('+');
        }
        else if ((ICR1 < 10 && ICR3 < 10) || (ICR1 < 10 && ICR3 < 10)  && (ICR4 > 100) && (ICR5 > 100)){
          Serial.println((unsigned int)ICR1 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR3 * 1);
          Serial.println('-');
          Serial.println(67 + (unsigned int)ICR4 * 1);
          Serial.println('-');
          Serial.println(67 + (unsigned int)ICR5 * 1);
          Serial.println('+');
        }
        else{
          Serial.println((unsigned int)ICR1 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR3 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR4 * 1);
          Serial.println('-');
          Serial.println((unsigned int)ICR5 * 1);
          Serial.println('+');
        }
        /* Clear pending interupts before restoring global interrupts so we don't
            immeadiatly trigger the check loop again.
        */
        TIFR1 = (1 << ICF1);
        TIFR3 = (1 << ICF3);
        TIFR4 = (1 << ICF4);
        TIFR5 = (1 << ICF5);
      }
      delay(520);
    }
  }
}
