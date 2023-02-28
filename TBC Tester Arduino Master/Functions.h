//Reading TBC mode and check the expected output
#include <Wire.h>
int Current_pin = 0;
int Current_pin_slave = 0;
int slave_circuit_conductivity = 0;
int circuit_conductivity_tested = 0;
char Correctness = 'T';

void print_fault_message(int OutputPin, int InputPin, int expected_circuit_state, int circuit_conductivity_tested)
{
  Serial.print("Output pin: "); Serial.print(OutputPin); Serial.print("    Input pin: ");Serial.println(InputPin);
  Serial.println("The circuit has problem, tested conductivity not match with expected");
  Serial.print("expected circuit circuit conductivity: "); Serial.println (expected_circuit_state);
  Serial.print("Tested conductivity: "); Serial.println (circuit_conductivity_tested);
}

void IO_pin_handling(int OutputPin, int InputPin, int expected_circuit_state)
{
  //OUTPUT pin handling
  if (OutputPin<=18){
    Current_pin = OutputPin+1;//current pin is the pin under operation
    pinMode(Current_pin,OUTPUT);
    digitalWrite(Current_pin, HIGH);
  }
  if (OutputPin>18 && OutputPin<=50){
    Current_pin = OutputPin+3;    
    pinMode(Current_pin,OUTPUT);
    digitalWrite(Current_pin, HIGH);
  }
  if (OutputPin>50 && OutputPin<=68){
    Current_pin_slave = OutputPin-50+1; 
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write('O');        // sends five bytes    
    Wire.write(Current_pin_slave);  //If outputpin is 52, pass 2 to slave
    Wire.endTransmission();    // stop transmitting
  }
  if (OutputPin>68 && OutputPin<=100){
    Current_pin_slave = OutputPin-50+3; 
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write('O');        // sends five bytes    
    Wire.write(Current_pin_slave);  //If outputpin is 73, pass 23+2 to slave, assign it to pin 25
    Wire.endTransmission();    // stop transmitting
  }  
   
  //Input pin handling

    if (InputPin<=18){
    Current_pin = InputPin+1;
    pinMode(Current_pin,INPUT);
    circuit_conductivity_tested = digitalRead(Current_pin);
    if (circuit_conductivity_tested!=expected_circuit_state){     
      Correctness='F';
    }
    else{
      Correctness='T';
    }
    Serial.print(OutputPin);Serial.print(", ");Serial.print(InputPin);Serial.print(", ");      
    Serial.print(Correctness);Serial.print(", "); Serial.print(expected_circuit_state);Serial.print(", ");
    Serial.print(circuit_conductivity_tested);Serial.println(", ");
  }

  if (InputPin>18 && InputPin<=50){
    Current_pin = InputPin+3;
    pinMode(Current_pin,INPUT);    
    circuit_conductivity_tested = digitalRead(Current_pin);

    if (circuit_conductivity_tested!=expected_circuit_state){
      //print_fault_message(OutputPin, InputPin, expected_circuit_state, circuit_conductivity_tested);      
      Correctness='F';
    }
    else{
      Correctness='T';
    }
    Serial.print(OutputPin);Serial.print(", ");Serial.print(InputPin);Serial.print(", ");      
    Serial.print(Correctness);Serial.print(", "); Serial.print(expected_circuit_state);Serial.print(", ");
    Serial.print(circuit_conductivity_tested);Serial.println(", ");    
  }

  if (InputPin>50 && InputPin<=68){
    Current_pin_slave = InputPin-50+1;
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write('I');        // sends five bytes    
    Wire.write(Current_pin_slave);  //If outputpin is 73, pass 23+2 to slave, assign it to pin 25
    Wire.endTransmission();    // stop transmitting
    Wire.requestFrom(8, 8);
    //request for slave pass back the conductivity
    if(Wire.available())
      {
        slave_circuit_conductivity = Wire.read();

    if (slave_circuit_conductivity!=expected_circuit_state){
      //print_fault_message(OutputPin, InputPin, expected_circuit_state, circuit_conductivity_tested);      
      Correctness='F';
    }
    else{
      Correctness='T';
    }
    Serial.print(OutputPin);Serial.print(", ");Serial.print(InputPin);Serial.print(", ");      
    Serial.print(Correctness);Serial.print(", "); Serial.print(expected_circuit_state);Serial.print(", ");
    Serial.print(slave_circuit_conductivity);Serial.println(", ");        
    }


    
  }  

  if (InputPin>68 && InputPin<=100){
    Current_pin_slave = InputPin-50+3;
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write('I');        // sends five bytes    
    Wire.write(Current_pin_slave);  //If outputpin is 73, pass 23+2 to slave, assign it to pin 25
    Wire.endTransmission();    // stop transmitting
    Wire.requestFrom(8, 8);
    //request for slave pass back the conductivity
    if(Wire.available())
    {
      slave_circuit_conductivity = Wire.read();

    if (slave_circuit_conductivity!=expected_circuit_state){  
      Correctness='F';
    }
    else{
      Correctness='T';
    }
    Serial.print(OutputPin);Serial.print(", ");Serial.print(InputPin);Serial.print(", ");      
    Serial.print(Correctness);Serial.print(", "); Serial.print(expected_circuit_state);Serial.print(", ");
    Serial.print(slave_circuit_conductivity);Serial.println(", ");        
    }
  }    
}

void Reset_pin_mode(int OutputPin)
{
    if (OutputPin<=18){
    Current_pin = OutputPin+1;//current pin is the pin under operation
    pinMode(Current_pin,OUTPUT);
    digitalWrite(Current_pin, LOW);
  }
  if (OutputPin>18 && OutputPin<=50){
    Current_pin = OutputPin+3;    
    pinMode(Current_pin,OUTPUT);
    digitalWrite(Current_pin, LOW);
  }
  if (OutputPin>50 && OutputPin<=68){
    Current_pin_slave = OutputPin-50+1; 
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write('R');        // sends five bytes, R stands for reset 
    Wire.write(Current_pin_slave);  //If outputpin is 52, pass 2 to slave
    Wire.endTransmission();    // stop transmitting
  }
  if (OutputPin>68 && OutputPin<=100){
    Current_pin_slave = OutputPin-50+3; 
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write('R');        // sends five bytes, R stands for reset    
    Wire.write(Current_pin_slave);  //If outputpin is 73, pass 23+2 to slave, assign it to pin 25
    Wire.endTransmission();    // stop transmitting
  }  
}

