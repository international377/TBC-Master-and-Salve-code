#include <Wire.h>

int salve_circuit_conductivity_tested = 3;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  Serial.begin(115200);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    char Pin_Mode = Wire.read(); // receive byte as a character
    //Serial.print("PINMODE is "); Serial.println(Pin_Mode);

  int Salve_pin_number = Wire.read();    // receive byte as an integer
    //Serial.print("PINNUMBER is ");Serial.println(Salve_pin_number);

  if (Pin_Mode=='O'){
    Serial.print("This is salve output pin: ");
    Serial.print(Salve_pin_number); 
    Serial.println(",   Pin mode is OUTPUT");     
    pinMode(Salve_pin_number, OUTPUT);
    digitalWrite(Salve_pin_number,HIGH);
  }

  if (Pin_Mode=='I'){
  Serial.print("This is input pin: ");
  Serial.print(Salve_pin_number);
  Serial.println("   Pin mode is INPUT");
  pinMode(Salve_pin_number, INPUT);    
  salve_circuit_conductivity_tested = digitalRead(Salve_pin_number); //Need to pass back the value to master to do comparision
  Serial.print("The input pin received conductivity is "); Serial.println(salve_circuit_conductivity_tested);
  
  
  }

  if (Pin_Mode=='R'){
  pinMode(Salve_pin_number, OUTPUT);
  digitalWrite(Salve_pin_number,LOW);
  Serial.print("This output pin is reseted to LOW: ");
  Serial.println(Salve_pin_number); 
  }

//test code

//End of test code
}

void requestEvent() {
 Wire.write(salve_circuit_conductivity_tested);  /*send string on request */
}