//const int LEDs[16] ={21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51};
unsigned long time;

//Define microphone input signal pins
#define micOutPin1 A0
#define micOutPin2 A1
#define micOutPin3 A2
#define micOutPin4 A3

// Define output pins
#define output 2
#define serialOut 3

// Define comparator threshold value
#define compThreshold 150

// Clear bit in sfr address
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
// Set bit in sfr address
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

// Interupt Service Routine vars
volatile byte sound = 0;
volatile long unsigned soundTime;

void setup() {
  // Setup serial out if connection present
  if(Serial) {
    Serial.begin(9600);
    pinMode(serialOut, OUTPUT);
  }
  
  // Enable LEDs out
  pinMode(output, OUTPUT);
  analogWrite(output, compThreshold);
  /* 
  for(int i=0; i < 16; i++){
    pinMode(LEDs[i], OUTPUT);
  } 
  */
  
  // Enable analog in
  pinMode(micOutPin1, INPUT);
  pinMode(micOutPin2, INPUT);
  pinMode(micOutPin3, INPUT);
  pinMode(micOutPin4, INPUT);

  // Enable comparator interrupt
  sbi(ADCSRB,ACME);
  cbi(ADMUX,MUX2);
  sbi(ADMUX,MUX1);
  cbi(ADMUX,MUX0);
  cbi(ADCSRA,ADEN); // Disable ADC
  ACSR =
    (0<<ACD) |  // Enable comparator
    (0<<ACDG) | // Comparator bandgap select AIN0
    (0<<ACO) |  // Set comparator output off
    (1<<ACI) |  // Comparator interupt flag
    (1<<ACIE) | // Enable comparator interupt
    (0<<ACIC) | // Disable comparator input capture
    (0<<ACIS1) | (0<ACIS0); // Comparator interrupt on output toggle
  
}
 
void loop() {
  //Read analog
  int mic1 = analogRead(micOutPin1);
  int mic2 = analogRead(micOutPin2);
  int mic3 = analogRead(micOutPin3);
  int mic4 = analogRead(micOutPin4);
  //struct distance { int analog, int distance };
  
/*
 * when(comparator for A0..A3 == 1) {
 *  time = millis();
 *  struct distance = { A0, distance(time); }
 * }
 */
 
  //struct distances[4] = {};
  
  //Find location
  //int LED = location(distances);
  if(sound == 1) {
    if(Serial) {
      //Write analog value to serial port: 
      Serial.println(soundTime);
    }
    //Turn on Associated LEDs
    //enable_led(LED);
    sound = 0; 
  }
}

ISR(ANALOG_COMP_vect) {
  soundTime = millis();
  sound=1;
}

/*
int distance(unsigned long time) {
  //Some calculation of time
  float distance = math;
  return distance;
}
​
int location(distances[]) {
  //Do some algorithm with analog and timestamp
  int location = math;
  return location;
}
​
void enable_led(int location) {
  digitalWrite(location, HIGH); 
}
*/
