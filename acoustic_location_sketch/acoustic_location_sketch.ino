#include <avr/interrupt.h>
#include <util/atomic.h>

/* Define microphone input signal pins */
#define ICPpin1 43  // ICP1 - ATmega2560 pin 47
#define ICPpin3 42  // ICP3 - ATmega2569 pin 9
#define ICPpin4 49  // ICP4 - ATmega2560 pin 35
#define ICPpin5 48  // ICP5 - ATmega2560 pin 36

void setup() {
  Serial.begin(115200);

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
    /* clear timer overflow flags */
    //    TIFR1 = (1<<TOV1);
    //    TIFR3 = (1<<TOV3);
    //    TIFR4 = (1<<TOV4);
    //    TIFR5 = (1<<TOV5);

    /* Reset timers */
    TCNT1 = 0;
    TCNT3 = 0;
    TCNT4 = 0;
    TCNT5 = 0;

    /* Check PORTL pins 0, 1, 6, and 7 for HIGH value */
    if (PINL & 0b11000011) {
      /* Disable global interrupts, and restore sreg state upon exit */
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        /* Wait one cycle.
            one cycle =
        */
        /*delay(20);

          /* The max difference in tics will equal: (max_dist / speed_of_sound) * tics_per_sec
            With a clock of of 250kHz each tick is 1/4 of a micro second, so multiply by 4 to
            get real time in micro seconds.
        */

        /*
         If Microphone 3 first recieves the signal and the bounce occured in (4,4) (4,5) (5,4) (5,5)

        */
        
        if (ICR4 < 10 && ICR5 >= 10  && ICR3 >= 10){

        Serial.print("Time 4: ");
        Serial.println(((unsigned int)ICR5 * 4) + 135);
        Serial.print("Time 3: ");
        Serial.println(((unsigned int)ICR4 * 4));
        Serial.print("Time 2: ");
        Serial.println(((unsigned int)ICR3 * 4) + (135));
        Serial.print("Time 1: ");
        Serial.println(((unsigned int)ICR1 * 4) + (135));
        
        Serial.println("Mic 3 First");
          
        }

        /*
         * If Microphone 4 first recieves the signal and the bounce occured in (1,4) (1,5) (2,4) (2,5)
         */

        else if (ICR5 < 10 && ICR4 >= 10 && ICR1 >= 10){

        Serial.print("Time 4: ");
        Serial.println(((unsigned int)ICR5 * 4));
        Serial.print("Time 3: ");
        Serial.println(((unsigned int)ICR4 * 4) + 135);
        Serial.print("Time 2: ");
        Serial.println(((unsigned int)ICR3 * 4) + (135));
        Serial.print("Time 1: ");
        Serial.println(((unsigned int)ICR1 * 4) + (135));
        
        Serial.println("Mic 4 First");
          
        }

        /*
         * If Microphone 1 first recieves the signal and the bounce occured in (1,4) (1,5) (2,4) (2,5)
         */

        else if (ICR1 < 10 && ICR5 >= 10 && ICR3 >= 10){

        Serial.print("Time 4: ");
        Serial.println(((unsigned int)ICR5 * 4) + (135));
        Serial.print("Time 3: ");
        Serial.println(((unsigned int)ICR4 * 4) + 135);
        Serial.print("Time 2: ");
        Serial.println(((unsigned int)ICR3 * 4) + (135));
        Serial.print("Time 1: ");
        Serial.println(((unsigned int)ICR1 * 4));
        
        Serial.println("Mic 1 First");
          
        }

         /*
         * If Microphone 2 first recieves the signal and the bounce occured in (4,1) (5,1) (4,2) (5,2)
         */

        else if (ICR3 < 10 && ICR1 >= 10 && ICR4 >= 10){
        Serial.print("Time 4: ");
        Serial.println((unsigned int)ICR5 * 4);
        Serial.print("Time 3: ");
        Serial.println((unsigned int)ICR4 * 4);
        Serial.print("Time 2: ");
        Serial.println((unsigned int)ICR3 * 4);
        Serial.print("Time 1: ");
        Serial.println((unsigned int)ICR1 * 4);
        
        Serial.print("Mic 2 First");
        
        }



        else if ((ICR4 < 10 && ICR5 < 10) || (ICR5 < 10 && ICR4 < 10) && (ICR1 > 100) && (ICR3 > 100) ) {

        /*
         * Middle of 3 and 4 for (3,4) (3,5)
         */
        
        Serial.print("Time 4: ");
        Serial.println(((unsigned int)ICR5 * 4));
        Serial.print("Time 3: ");
        Serial.println(((unsigned int)ICR4 * 4));
        Serial.print("Time 2: ");
        Serial.println(((unsigned int)ICR3 * 4) + 2*(135));
        Serial.print("Time 1: ");
        Serial.println(((unsigned int)ICR1 * 4) + 2*(135));
        
        Serial.print("Middle of 3 and 4");

        }

        /*
         * Middle of 4 and 1 for (1,3) (2,3)
         */

        else if ((ICR5 < 10 && ICR1 < 10) || (ICR5 < 10 && ICR1 < 10)  && (ICR4 > 100) && (ICR3 > 100)){

        Serial.print("Time 4: ");
        Serial.println(((unsigned int)ICR5 * 4));
        Serial.print("Time 3: ");
        Serial.println(((unsigned int)ICR4 * 4) + 2*(135));
        Serial.print("Time 2: ");
        Serial.println(((unsigned int)ICR3 * 4) + 2*(135));
        Serial.print("Time 1: ");
        Serial.println(((unsigned int)ICR1 * 4));
        
        Serial.print("Middle of 1 and 4");

        }

        else if ((ICR1 < 10 && ICR3 < 10) || (ICR1 < 10 && ICR3 < 10)  && (ICR4 > 100) && (ICR5 > 100)){

        Serial.print("Time 4: ");
        Serial.println(((unsigned int)ICR5 * 4) + 2*(135));
        Serial.print("Time 3: ");
        Serial.println(((unsigned int)ICR4 * 4) + 2*(135));
        Serial.print("Time 2: ");
        Serial.println(((unsigned int)ICR3 * 4));
        Serial.print("Time 1: ");
        Serial.println(((unsigned int)ICR1 * 4));
        
        Serial.print("Middle of 1 and 2");

        }
        
        else
        
        {
        Serial.print("Time 4: ");
        Serial.println((unsigned int)ICR5 * 4);
        Serial.print("Time 3: ");
        Serial.println((unsigned int)ICR4 * 4);
        Serial.print("Time 2: ");
        Serial.println((unsigned int)ICR3 * 4);
        Serial.print("Time 1: ");
        Serial.println((unsigned int)ICR1 * 4);
        
        Serial.print("Main loop");
        
        }
        /* Store ICR values to export */
        //      unsigned int icr[4];
        //      icr[0] = ICR1;
        //      icr[1] = ICR3;
        //      icr[2] = ICR4;
        //      icr[3] = ICR5;

        /* We should never run into an overflow because we reset the clocks before each loop.
            To check for overflow look at the overflow flag: TOVn
        */

        /* Clear pending interupts before restoring global interrupts so we don't
            immeadiatly trigger the check loop again.
        */
        TIFR1 = (1 << ICF1);
        TIFR3 = (1 << ICF3);
        TIFR4 = (1 << ICF4);
        TIFR5 = (1 << ICF5);
      }
      Serial.println("-----------------------");
    }
  }
}
