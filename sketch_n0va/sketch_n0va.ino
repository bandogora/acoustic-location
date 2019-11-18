//const int LEDs[16] ={21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51};

//Define microphone input signal pins
#define micOut1 53
#define micOut2 49
#define micOut3 47
#define micOut4 45

// Define output pin
#define output 31

void setup() {
  // Setup serial out if connection present
  if(Serial) {
    Serial.begin(9600);
  }

  // Enable LEDs out
  pinMode(output, OUTPUT);
  /* 
  for(int i=0; i < 16; i++){
    pinMode(LEDs[i], OUTPUT);
  } 
  */
  
  // Enable analog in
  pinMode(micOut1, LOW);
  pinMode(micOut2, LOW);
  pinMode(micOut3, LOW);
  pinMode(micOut4, LOW);
  
}
 
void loop() {
  //Read analog
  int mic1 = digitalRead(micOut1);
  int mic2 = digitalRead(micOut2);
  int mic3 = digitalRead(micOut3);
  int mic4 = digitalRead(micOut4);

  boolean on = (mic1 || mic2 || mic3 || mic4);
  if( on == true) {
    Serial.println(micros());
    //Start calculatttion
  }
}

void enable_led(int location) {
  digitalWrite(location, HIGH); 
}
