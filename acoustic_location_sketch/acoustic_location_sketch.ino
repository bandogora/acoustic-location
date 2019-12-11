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

/* Define lenght */
unsigned int distance = 0.4;
volatile double x;
volatile double y;

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
  TIFR1 = (1<<ICF1);                  // Clear pending interupts and Overflow Flag Interrupt
  TCCR1A = 0;                         // Disable compare interrupts (necessary for arduino) and set WGM to normal mode
  TCCR1B = (1<<CS11)|(1<<CS10);       // Initiate timer with /64 prescale
  TIMSK1 = (1<<ICIE1);                // Enable 16-bit Timer Capture Event Interrupt and Overflow Interrupt
  
  /* Timer 3 setup */
  TIFR3 = (1<<ICF3);
  TCCR3A = 0;
  TCCR3B = (1<<CS31)|(1<<CS30);
  TIMSK1 = (1<<ICIE3);
  
  /* Timer 4 setup */
  TIFR4 = (1<<ICF4);
  TCCR4A = 0;
  TCCR4B = (1<<CS41)|(1<<CS40);
  TIMSK4 = (1<<ICIE4);
  
  /* Timer 5 setup */
  TIFR5 = (1<<ICF5);
  TCCR5A = 0;
  TCCR5B = (1<<CS51)|(1<<CS50);
  TIMSK5 = (1<<ICIE5);
}
 
void loop() {
  /* Check input for state change */
  bool in1 = digitalRead(ICPpin1);
  bool in2 = digitalRead(ICPpin3);
  bool in3 = digitalRead(ICPpin4);
  bool in4 = digitalRead(ICPpin5);
  bool on = !(in1 & in2 & in3 & in4); // Invert for falling edge
  
  if (on) {
    /* Reset timers */
    TCNT1 = 0;
    TCNT3 = 0;
    TCNT4 = 0;
    TCNT5 = 0;
    
    /* Read ICR registers */
    unsigned char sreg = SREG;        // Save global interrupt flag
    noInterrupts();                   // Disable arduino interrupts
    unsigned int icr[4];              // Read ICRs
    icr[0] = ICR1;
    icr[1] = ICR3;
    icr[2] = ICR4;
    icr[3] = ICR5;
    SREG = sreg;                      // Restore global interrupt flag
    interrupts();                     // Enable arduino interrupts

    /* Convert timer tics to seconds */
    double time_input[4];
    for (int i = 0; i < 4; i++) {
      time_input[i] = icr[i] * 0.000004;
    }

    getPosFromTimes(time_input);
    Serial.print("x: ");
    Serial.println(x);
    Serial.print("y: ");
    Serial.println(y);
    
    /* Determine which pin changed state first */
    
    /* Test
    Serial.print("Time 1: ");
    Serial.println(icr[0]);
    Serial.print("Time 2: ");
    Serial.println(icr[1]);
    Serial.print("Time 3: ");
    Serial.println(icr[2]);
    Serial.print("Time 4: ");
    Serial.println(icr[3]);
    */
  }
}

void getPosFromTimes(double Xt[4]) {
  // Xt is an array that stores the TOA for mics from 0 to 3
  // Distance is the length of the side of the square board in meter

  //S data structure could be stored as global 
  double S[4][2] = { {0,0},{1,0},{1,1},{0,1} };


  for(int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      S[i][j] *= distance;
    }
  }


  double c = 340;
  
  int min_index = minimum_index(Xt);

  int x_next = 0;
  int x_last = 0;

  //min_index = 1;

  switch (min_index) {
    case 0:
      x_next = 1;
      x_last = 3;
      break;
    case 1:
      x_next = 2;
      x_last = 0;
      break;
    case 2:
      x_next = 3;
      x_last = 1;
      break;
    case 3:
      x_next = 0;
      x_last = 2;
      break;
  }

  double Xb;
  double Xc;

  Xb = c * (Xt[x_next] - Xt[min_index]);
  Xc = c * (Xt[x_last] - Xt[min_index]);

  double A;
  double B;
  double C;
  double delta;

  double r1;
  double r2;

  double x_res;
  double y_res;

  
  A = pow(Xb, 2) + pow(Xc, 2) - 1;

  B = -(  Xb *( 1 - pow(Xb, 2))   +   Xc*(1 - pow(Xc, 2))  );

  C = pow((0.5 - 0.5 * pow(Xb, 2)), 2) + pow((0.5 - 0.5 * pow(Xc, 2)), 2);

  //delta = sqrt(B ^ 2 - 4 * A * C);
  delta = sqrt(pow(B, 2) - 4 * A * C);

  r1 = (-B + delta) / (2 * A);
  r2 = (-B - delta) / (2 * A);

  x_res = 0.5 - 0.5 * pow(Xb, 2) - Xb * r2;
  y_res = 0.5 - 0.5 * pow(Xc, 2) - Xc * r2;


  switch (min_index) {
  case 0:
    x_res = y_res;
    y_res = x_res;
    break;
  case 1:
    x_res = distance - y_res;
    y_res = x_res;
    break;
  case 2:
    x_res = distance - x_res;
    y_res = distance - y_res;
    break;
  case 3:
    x_res = y_res;
    y_res = distance - x_res;
    break;
  }

  x = x_res;
  y = y_res;


}

int minimum_index(double in[4]) {
  int mini_index = 0;
  double minimum = in[0];
  for (int i = 0; i < 4;i++) {
    if (minimum > in[i]) {
      mini_index = i;
      minimum = in[i];
    }

  }
  return mini_index;
}
