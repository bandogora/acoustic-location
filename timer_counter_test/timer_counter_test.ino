/* 
 * README:
 * This program makes some assumptions.
 * 1. You are using an ATmega2560 or Arduino Mega
 * 2. You have access to all 4 16-bit timers (Requires physical modification on Arduino)
 * 3. Your microphones input signal is digital
 * 4. You are using an inverting comparator (Falling edge trigger)
 */

/* Define microphone input signal pins */
#define ICPpin1 14                    // ICP1 - ATmega2560 pin 47
#define ICPpin3 21                    // ICP3 - ATmega2569 pin 9
#define ICPpin4 49                    // ICP4 - ATmega2560 pin 35
#define ICPpin5 48                    // ICP5 - ATmega2560 pin 36

/* Define output pins */
//#define output 31

void setup() {
  /* Begin serial if present */
  if (Serial) {
    Serial.begin(500000);
  }
  
  /* Pull up digital input pins */
  pinMode(ICPpin1, INPUT_PULLUP);
  pinMode(ICPpin3, INPUT_PULLUP);
  pinMode(ICPpin4, INPUT_PULLUP);
  pinMode(ICPpin5, INPUT_PULLUP);

  /* Timer 1 setup */
  TIFR1 = (1<<ICF1)|(1<<TOV1);         // Clear pending interupts and Overflow Flag Interrupt
  TCCR1A = 0;                          // Disable compare interrupts (necessary for arduino) and set WGM to normal mode
  TCCR1B = (1<<CS11)|(1<<CS10);        // Initiate timer with /64 prescale
  TIMSK1 = (1<<ICIE1)|(1<<TOIE1);      // Enable 16-bit Timer Capture Event Interrupt and Overflow Interrupt
  TCNT1 = 0;                           // Reset timer
  
  /* Timer 3 setup */
  TIFR3 = (1<<ICF3)|(1<<TOV3);
  TCCR3A = 0;
  TCCR3B = (1<<CS31)|(1<<CS30);
  TIMSK1 = (1<<ICIE3)|(1<<TOIE3);
  TCNT3 = 0;
  
  /* Timer 4 setup */
  TIFR4 = (1<<ICF4)|(1<<TOV4);
  TCCR4A = 0;
  TCCR4B = (1<<CS41)|(1<<CS40);
  TIMSK4 = (1<<ICIE4)|(1<<TOIE4);
  TCNT4 = 0;
  
  /* Timer 5 setup */
  TIFR5 = (1<<ICF5)|(1<<TOV5);
  TCCR5A = 0;
  TCCR5B = (1<<CS51)|(1<<CS50);
  TIMSK5 = (1<<ICIE5)|(1<<TOIE5);
  TCNT5 = 0;
}
 
void loop() {
  /* Check input for state change */
  bool in1 = digitalRead(ICPpin1);
  bool in2 = digitalRead(ICPpin3);
  bool in3 = digitalRead(ICPpin4);
  bool in4 = digitalRead(ICPpin5);
  bool on = !(in1 & in2 & in3 & in4); // Invert for falling edge
  
  if (on) {
    char first =0;
    if (in1 == 0) {
      first = '0';
    }
    if (in2 == 0) {
      first = '1';
    }
    if (in3 == 0) {
      first = '2';
    }
    if (in4 == 0) {
      first = '3';
    }
    Serial.print(first);
    /* Read ICR registers */
    unsigned char sreg = SREG;        // Save global interrupt flag
    noInterrupts();                   // Disable arduino interrupts

    unsigned int icr[4];              // Read ICRs
    icr[0] = ICR1;
    icr[1] = ICR3;
    icr[2] = ICR4;
    icr[3] = ICR5;
    unsigned char tov[4];             // Read TOV flags
    tov[0] = TOV1;
    tov[1] = TOV3;
    tov[2] = TOV4;
    tov[3] = TOV5;
    
    SREG = sreg;                      // Restore global interrupt flag
    interrupts();                     // Enable arduino interrupts

    
    //timeAdjust(icr);


    
    Serial.print("Time 1: ");
    Serial.println(icr[0]);
    Serial.println(tov[0]);
    Serial.print("Time 2: ");
    Serial.println(icr[1]);
    Serial.print("Time 3: ");
    Serial.println(icr[2]);
    Serial.print("Time 4: ");
    Serial.println(icr[3]);
  }
}

unsigned int timeAdjust(char first, unsigned int icr[]) {
  unsigned int times[4];
  switch (first) {
    case '1':
      times[0] = 0;
      break;
    case '2':
      times[1] = 0;
      break;
    case '3':
      times[2] = 0;
      break;
    case '4':
      times[3] = 0;
      break;
  }
  
  for (int i = 1; i < 5; i++) {
    
  }
}
