// Define microphone input signal pins
#define ICPpin1 14  // pin 47 ICP1
#define ICPpin3 21  // pin 9 ICP3
#define ICPpin4 49  // pin 35 ICP4
#define ICPpin5 48  // pin 36 ICP5

// Define output pin
//#define output 31

void setup() {
  Serial.begin(19200);
  
  // Pull up digital input pins
  pinMode(ICPpin1, INPUT_PULLUP);
  pinMode(ICPpin3, INPUT_PULLUP);
  pinMode(ICPpin4, INPUT_PULLUP);
  pinMode(ICPpin5, INPUT_PULLUP);

  // Timer 1 setup
 
  TIFR1 = 1<<ICF1;              // Clear pending interupts
  TCCR1B = (1<<CS11)|(1<<CS10); // Initiate timer with /64 prescale
  TIMSK1 = 1<<ICIE1;            // Enable 16-bit Timer Capture Event Interrupt
  TCNT1 = 0;                    // Reset timer
  
  // Timer 3 setup
  TIFR3 = 1<<ICF3;
  TCCR3B = (1<<CS31)|(1<<CS30);
  TIMSK1 = 1<<ICIE3;
  TCNT3 = 0;
  
  // Timer 4 setup
  TIFR4 = 1<<ICF4;
  TCCR4B = (1<<CS41)|(1<<CS40);
  TIMSK4 = 1<<ICIE4;
  TCNT4 = 0;
  
  // Timer 5 setup
  TIFR5 = 1<<ICF5;
  TCCR5B = (1<<CS51)|(1<<CS50);
  TIMSK5 = 1<<ICIE5;
  TCNT5 = 0;
}
 
void loop() {

  
  // Read Input Capture Register
  bool in1 = digitalRead(ICPpin1);
  bool in2 = digitalRead(ICPpin3);
  bool in3 = digitalRead(ICPpin4);
  bool in4 = digitalRead(ICPpin5);
  
  bool on = !(in1 | in2);
  if (!in4) {
    Serial.println(ICR5); // Time of interrupt
    //Serial.println(ICR3); // Time of interrupt
    delay(100);  
  }

}
