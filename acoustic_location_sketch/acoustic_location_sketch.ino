/* 
 * README:
 * This program makes some assumptions.
 * 1. You are using an ATmega2560 or Arduino Mega
 * 2. You have access to all 4 16-bit timers (Requires physical modification on Arduino)
 * 3. Your microphones input signal is digital
 * 4. You are using an inverting comparator (Falling edge trigger)
 */

/* Define microphone input signal pins */
#define ICPpin1 43                    // ICP1 - ATmega2560 pin 47
#define ICPpin3 42                    // ICP3 - ATmega2569 pin 9
#define ICPpin4 49                    // ICP4 - ATmega2560 pin 35
#define ICPpin5 48                    // ICP5 - ATmega2560 pin 36

void setup() {

  Serial.begin(115200);
  
  /* Pull up digital input pins */
  DDRL |= 0;
//  pinMode(ICPpin1, INPUT);
//  pinMode(ICPpin3, INPUT);
//  pinMode(ICPpin4, INPUT);
//  pinMode(ICPpin5, INPUT);

//  int max_diff = (max_dist / speed_of_sound) * tics_per_sec; // Should be about 425

  /* Timer 1 setup */
  TIFR1 = (1<<ICF1);    // Clear pending interupts and Overflow Flag Interrupt
  TCCR1A = 0;           // Disable compare interrupts (necessary for arduino) and set WGM to normal mode
  TCCR1B = (0<<ICNC1)|  // Turn off noise filtering
  (1<<ICES1)|           // Set input capture edge to rising
  (0<<WGM13)|           // Set WGM to normal
  (0<<WGM12)|
  (1<<CS11)|            // CS bits set prescale to /64
  (1<<CS10);
  TIMSK1 = (1<<ICIE1)|  // Enable 16-bit Timer Capture Event Interrupt
  (0<<TOIE1);           // Disable Overflow Interrupt
  TIFR1 = (1<<TOV1);    // Clear timer overflow flag
  
  /* Timer 3 setup */
  TIFR3 = (1<<ICF3);
  TCCR3A = 0;
  TCCR3B = (0<<ICNC3)|(1<<ICES3)|(0<<WGM33)|(0<<WGM32)|(1<<CS31)|(1<<CS30);
  TIMSK1 = (1<<ICIE3)|(0<<TOIE3);
  TIFR3 = (1<<TOV3);
  
  /* Timer 4 setup */
  TIFR4 = (1<<ICF4);
  TCCR4A = 0;
  TCCR4B = (0<<ICNC4)|(1<<ICES4)|(0<<WGM43)|(0<<WGM42)|(1<<CS41)|(1<<CS40);
  TIMSK4 = (1<<ICIE4)|(0<<TOIE4);
  TIFR4 = (1<<TOV4);
  
  /* Timer 5 setup */
  TIFR5 = (1<<ICF5);
  TCCR5A = 0;
  TCCR5B = (0<<ICNC5)|(1<<ICES5)|(0<<WGM53)|(0<<WGM52)|(1<<CS51)|(1<<CS50);
  TIMSK5 = (1<<ICIE5)|(0<<TOIE5);
  TIFR5 = (1<<TOV5);

  
}

//loop vars
  unsigned char sreg;

 
void loop() {
  
  
  while(1) {
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
      
    /* Check input for state change */
//    bool in1 = digitalRead(ICPpin1);
//    bool in2 = digitalRead(ICPpin3);
//    bool in3 = digitalRead(ICPpin4);
//    bool in4 = digitalRead(ICPpin5);
//    bool on = (in1 | in2 | in3 | in4);
    //bool on = ((PINL & 0b10000000) | (PINL & 0b01000000) | (PINL & 0b00000010) | (PINL & 0b00000001)); 
   // bool on = (PINL & 0b11000011);
    
    if (PINL & 0b11000011) {
      
      /* Read ICR registers */
      sreg = SREG;      // Save global interrupt flag, neccessary for avr
      noInterrupts();                   // Disable arduino interrupts

      delay(20);

      Serial.print("Time 1: ");
      Serial.println((unsigned int)ICR5 * 4);
      Serial.print("Time 2: ");
      Serial.println((unsigned int)ICR4 * 4);
      Serial.print("Time 3: ");
      Serial.println((unsigned int)ICR3 * 4);
      Serial.print("Time 4: ");
      Serial.println((unsigned int)ICR1 * 4);

      
//      unsigned int icr[4];              // Read ICRs
//      icr[0] = ICR1;
//      icr[1] = ICR3;
//      icr[2] = ICR4;
//      icr[3] = ICR5;

      /* Check for overflow flag and adjust */
//      long max_count = 65536; // 2^16
//      if (TOV1 == 1) {
//        Serial.println("TOV1");
//        //icr[0] += max_count; 
//      };
//      if (TOV3 == 1) {
//        Serial.println("TOV3");
//        //icr[1] += max_count;
//      };
//      if (TOV4 == 1) {
//        Serial.println("TOV4");
//        //icr[2] += max_count;
//      };
//      if (TOV5 == 1) {
//        Serial.println("TOV5");
//        //icr[3] += max_count;
//      };

      TIFR1 = (1<<ICF1);
      TIFR3 = (1<<ICF3);
      TIFR4 = (1<<ICF4);
      TIFR5 = (1<<ICF5);
      
      SREG = sreg;                      // Restore global interrupt flag
      interrupts();                     // Enable arduino interrupts
      
      // Test
      
      Serial.println("-----------------------");
      //delay(500);
    }
  }
}
