// Define microphone input signal pins
#define micOut1 47  //ICP1
#define micOut2 9   //ICP3
#define micOut3 35  //ICP4
#define micOut4 36  //ICP5

// Define output pin
#define output 31

void setup() {
  Serial.begin(9600);
  
  // Pull up digital in pins
  pinMode(micOut1, INPUT_PULLUP);
  pinMode(micOut2, INPUT_PULLUP);
  pinMode(micOut3, INPUT_PULLUP);
  pinMode(micOut4, INPUT_PULLUP);

//  for (int n = 1; n < 6; n++) {
//    if ( n != 2) {
//      TIFR[n] = 1<<ICF[n];    // Clear ICF1. Clear pending interrupts
//      TCCR[n]B = 1<<CS[n]0;   // Timer clock on, no pre-scalling
//      TIMSK[n] = 1<<ICIE[n];  // Enable 16-bit Timer Capture Event Interrupt
//      // |(0<<ICES[n]);       // set edge detection 0=falling 1=rising
//    }
//  }

  TIFR1 = 1<<ICF1;
  TCCR1B = 1<<CS10;
  TIMSK1 = 1<<ICIE1;
  TIFR3 = 1<<ICF3;
  TCCR3B = 1<<CS30;
  TIMSK3 = 1<<ICIE3;
}
 
void loop() {

  
  // Read Input Capture Register
  bool in1 = digitalRead(micOut1);
  
  word timer_val1 = ICR1;
  if (!in1) {
    Serial.println("On");
    Serial.println(timer_val1);
    Serial.println(TCNT1);
    Serial.println(ICF1);    
    delay(100);  
  }
  //TCNT1 = 0;
//  bool in2 = digitalRead(micOut2);
//  word timer_val2 = ICR3;
//  //Serial.print(timer_val2);
//  bool in3 = digitalRead(micOut3);
//  word timer_val3 = ICR4;
//  bool in4 = digitalRead(micOut4);
//  word timer_val4 = ICR5;
}
