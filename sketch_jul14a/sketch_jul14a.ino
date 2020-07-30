#define BAUD 9600
//led 
#define led 13
#define pump 8


void setup(){
  Serial.begin(BAUD);
  pinMode(led, OUTPUT);
  pinMode(pump, OUTPUT);
}

void loop(){
  String input;
  //If any input is detected in arduino
  if(Serial.available() > 0){
    //read the whole string until '\n' delimiter is read
    input = Serial.readStringUntil('\n');
    //If input == "ON" then turn on the led 
    
    if (input.equals("ON")){
      digitalWrite(led, HIGH);
      digitalWrite(pump, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      digitalWrite(pump, LOW);
    } 
  }
}
