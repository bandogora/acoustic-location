const int LEDs[16] ={21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51};
unsigned long time;
​
void setup() {
  //Setup serial connection if present or enable LED out
  if(Serial) {
    Serial.begin(9600);
    pinMode(1, OUTPUT); //Serial out
  }
  else {
    //Enable LEDs out
    for(int i=0; i < 16; i++){
      pinMode(LEDs[i], OUTPUT);
    } 
  }
  
  //Enable analog in
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
}
 
void loop() {
  //Read analog
  int A0 = analogRead(A0);
  int A1 = analogRead(A1);
  int A2 = analogRead(A2);
  int A3 = analogRead(A3);
  struct distance { int analog, int distance };
​
  //Analog compartor needed to assign interupts
//  attachInterrupt();
/*
 * when(comparator for A0..A3 == 1) {
 *  time = millis();
 *  struct distance = { A0, distance(time); }
 * }
 */
​
  struct distances[4] = {};
​
  //Find location
  int LED = location(distances);
​
  if(Serial) {
    //Write analog value to serial port:
    Serial.println(LED);
  }
  else {
    //Turn on Associated LEDs
    enable_led(LED);
  }        
}
​
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
