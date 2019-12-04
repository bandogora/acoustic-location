unsigned long time;

//const int LEDs[16] ={21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51};

//Define microphone input signal pins
#define micOut1 53
#define micOut2 51
#define micOut3 49
#define micOut4 47

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
  pinMode(micOut2, INPUT_PULLUP);
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
  time = millis();
  Mic mic1;
  mic1.name = "mic1";
  Mic mic2;
  mic2.name = "mic2";
  Mic mic3;
  mic3.name = "mic3";
  Mic mic4;
  mic4.name = "mic4";
  
  //Read analog
  bool in1 = digitalRead(micOut1);
  bool in2 = digitalRead(micOut2);
  bool in3 = digitalRead(micOut3);
  bool in4 = digitalRead(micOut4);

  mic1.on = !in1;
  mic2.on = !in2;

  //Serial.print(mic1.on);
  //Serial.println(mic2.on);

  boolean on = !(in1 & in2);// && in3 && in4);
  if(on) {
    
    mic1.start_time = time;
    mic2.start_time = time;
      

    if (mic1.on) {
      Serial.print(mic1.name);
      Serial.print(" time=");
      Serial.println(mic1.start_time);
      delay(10);
    } 
    if (mic2.on) {
      Serial.print(mic2.name);
      Serial.print(" time=");
      Serial.println(mic2.start_time);
      delay(100);
    }
      
    //Start calculatttion
  }
}

void enable_led(int location) {
  digitalWrite(location, HIGH); 
}
