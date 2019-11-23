unsigned long time;

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
  pinMode(micOut1, INPUT_PULLUP);
  //pinMode(micOut2, INPUT_PULLUP);
  //pinMode(micOut3, INPUT_PULLUP);
  //pinMode(micOut4, INPUT_PULLUP);
}

class Mic {
  public:
  String name;
  bool on;
  unsigned long start_time;
};
 
void loop() {
  //Start time in micros
  time = micros();
  
  //Read analog
  bool in1 = digitalRead(micOut1);
  bool in2 = digitalRead(micOut2);
  bool in3 = digitalRead(micOut3);
  bool in4 = digitalRead(micOut4);

  boolean on = !(in1 || in2 || in3 || in4);
  if(on) {
    
    Mic mic1;
    mic1.name = "mic1";
    mic1.on = in1;
    mic1.start_time = time;

    Serial.print(mic1.name);
    Serial.print(" time:");
    Serial.println(mic1.start_time);
    delay(100);
    //Start calculatttion
  }
}

void enable_led(int location) {
  digitalWrite(location, HIGH); 
}
