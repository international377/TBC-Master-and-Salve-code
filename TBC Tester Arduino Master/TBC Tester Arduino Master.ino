//Array for Mode selection and TBC selection
#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))
#include "Array.h";
#include "Functions.h";
#include <Wire.h>

String ModeSelector[] = { "SD", "AUTO", "CM", "FOR", "SB", "REV" };
String TBCSelector[] = { "Max Brake", "Min Brake", "Coasting", "Min Power", "Max Power", "Em Brake" };
String Mode_Selector = "";
String TBC_Selector = "X";


//variable setup
int Total_number_of_pin = 100;
int expected_circuit_state = 0;
char Pin_Mode;
long int t1 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();  // join i2c bus (address optional for master)
}

void loop() {
  delay(1000);
  Serial.println("Time, Mode Selector, TBC Selector, Output Pin, Input Pin, Correctness, Expected Circuit State, Tested Circuit State");
  // put your main code here, to run repeatedly:
  //Mode selector
  for (int i = 0; i < ELEMENTS(ModeSelector); i++) {

    //Reading "SD" Modes, not doing the TBC combination
    if (ModeSelector[i] == "SD") {
      Mode_Selector = ModeSelector[i];
      Serial.print("Testing in ");
      Serial.print(Mode_Selector);
      Serial.print(" mode will start in 10s");
      Serial.println(",");
      delay(10000);
      Serial.print("Testing in ");
      Serial.print(Mode_Selector);
      Serial.print(" mode started");
      Serial.println(",");
      delay(1000);


      //assigning input and output to Traction Brake Controller pins by using for loop and test for SD mode output
      for (int OutputPin = 1; OutputPin <= Total_number_of_pin; OutputPin++) {
        //Avoid redundant case checked in previous loop, and avoid self testing, e.g. [1][1], [2][2], [3][3] test
        for (int InputPin = (OutputPin + 1); InputPin <= Total_number_of_pin; InputPin++) {
          //Check if the expected result is "closed case" listed in the array
          //Reading the elements in the SD MODE Selector
          for (int k = 0; k < ELEMENTS(SD_Close); k++) {

            if (SD_Close[k][0] == OutputPin && SD_Close[k][1] == InputPin) {
              expected_circuit_state = 1;
              break;
            } else {
              expected_circuit_state = 0;
            }
          }
          t1 = millis();
          Serial.print(t1 / 1000);
          Serial.print(", ");
          Serial.print(Mode_Selector);
          Serial.print(", ");
          Serial.print(TBC_Selector);
          Serial.print(", ");
          IO_pin_handling(OutputPin, InputPin, expected_circuit_state);
        }
        Reset_pin_mode(OutputPin);
      }
    }

    //Reading "AUTO" Modes, not doing the TBC combination
    else if (ModeSelector[i] == "AUTO") {
      Mode_Selector = ModeSelector[i];
      Serial.print("Testing in ");
      Serial.print(Mode_Selector);
      Serial.print(" mode will start in 10s");
      Serial.println(",");
      delay(10000);
      Serial.print("Testing in ");
      Serial.print(Mode_Selector);
      Serial.print(" mode started");
      Serial.println(",");
      delay(1000);


      //assigning input and output to Traction Brake Controller pins by using for loop and test for AUTO mode output
      for (int OutputPin = 1; OutputPin <= Total_number_of_pin; OutputPin++) {
        //Avoid redundant case checked in previous loop, and avoid self testing, e.g. [1][1], [2][2], [3][3] test
        for (int InputPin = (OutputPin + 1); InputPin <= Total_number_of_pin; InputPin++) {
          //Check if the expected result is "closed case" listed in the array
          //Reading the elements in the AUTO MODE Selector
          for (int k = 0; k < ELEMENTS(AUTO_Close); k++) {

            if (AUTO_Close[k][0] == OutputPin && AUTO_Close[k][1] == InputPin) {
              expected_circuit_state = 1;
              break;
            } else {
              expected_circuit_state = 0;
            }
          }
          t1 = millis();
          Serial.print(t1 / 1000);
          Serial.print(", ");
          Serial.print(Mode_Selector);
          Serial.print(", ");
          Serial.print(TBC_Selector);
          Serial.print(", ");
          IO_pin_handling(OutputPin, InputPin, expected_circuit_state);
        }
        Reset_pin_mode(OutputPin);
      }
    }

    //Reading "CM" Modes with TBC combination
    else if (ModeSelector[i] == "CM") {
      //TBC mode selector
      for (int j = 0; j < ELEMENTS(TBCSelector); j++) {
        Mode_Selector = ModeSelector[i];
        TBC_Selector = TBCSelector[j];

        Serial.print("Testing in ");
        Serial.print(Mode_Selector);
        Serial.print(TBC_Selector);
        Serial.print(" mode will start in 10s");
        Serial.println(",");
        delay(10000);
        Serial.print("Testing in ");
        Serial.print(Mode_Selector);
        Serial.print(TBC_Selector);
        Serial.print(" mode started");
        Serial.println(",");
        delay(1000);

        //assigning input and output to Traction Brake Controller pins by using for loop and test for CM mode output
        for (int OutputPin = 1; OutputPin <= Total_number_of_pin; OutputPin++) {
          //Avoid redundant case checked in previous loop, and avoid self testing, e.g. [1][1], [2][2], [3][3] test
          for (int InputPin = (OutputPin + 1); InputPin <= Total_number_of_pin; InputPin++) {
            //Check if the expected result is "closed case" listed in the array
            //Reading the elements in the CM MODE Selector
            for (int k = 0; k < ELEMENTS(CM_Close); k++) {

              if (CM_Close[k][0] == OutputPin && CM_Close[k][1] == InputPin) {
                expected_circuit_state = 1;
                break;
              } else {
                expected_circuit_state = 0;
              }
            }
            //Check if the expected result is "closed case" listed in the array
            //Reading the elements in the CM MODE Selector
            if (expected_circuit_state == 0) {
              switch (j) {
                case 0:  //Reading Max Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Brake_Max_Close); k++) {

                    if (Brake_Max_Close[k][0] == OutputPin && Brake_Max_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 1:  //Reading Min Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Brake_Min_Close); k++) {

                    if (Brake_Min_Close[k][0] == OutputPin && Brake_Min_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 2:  //Reading Coasting TBC Array
                  for (int k = 0; k < ELEMENTS(Coasting_Close); k++) {

                    if (Coasting_Close[k][0] == OutputPin && Coasting_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 3:  //Reading Min motor TBC Array
                  for (int k = 0; k < ELEMENTS(Motor_Min_Close); k++) {

                    if (Motor_Min_Close[k][0] == OutputPin && Motor_Min_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 4:  //Reading Max motor TBC Array
                  for (int k = 0; k < ELEMENTS(Motor_Max_Close); k++) {

                    if (Motor_Max_Close[k][0] == OutputPin && Motor_Max_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 5:  //Reading Em Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Em_Brake_Close); k++) {

                    if (Em_Brake_Close[k][0] == OutputPin && Em_Brake_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
              }
            }
            t1 = millis();
            Serial.print(t1 / 1000);
            Serial.print(", ");
            Serial.print(Mode_Selector);
            Serial.print(", ");
            Serial.print(TBC_Selector);
            Serial.print(", ");
            IO_pin_handling(OutputPin, InputPin, expected_circuit_state);
          }
          Reset_pin_mode(OutputPin);
        }
      }
    }

    //Reading "FOR" Modes with TBC combination
    else if (ModeSelector[i] == "FOR") {
      //TBC mode selector
      for (int j = 0; j < ELEMENTS(TBCSelector); j++) {
        Mode_Selector = ModeSelector[i];
        TBC_Selector = TBCSelector[j];

        Serial.print("Testing in ");
        Serial.print(Mode_Selector);
        Serial.print(TBC_Selector);
        Serial.print(" mode will start in 10s");
        Serial.println(",");
        delay(10000);
        Serial.print("Testing in ");
        Serial.print(Mode_Selector);
        Serial.print(TBC_Selector);
        Serial.print(" mode started");
        Serial.println(",");
        delay(1000);

        //assigning input and output to Traction Brake Controller pins by using for loop and test for FOR mode output
        for (int OutputPin = 1; OutputPin <= Total_number_of_pin; OutputPin++) {
          //Avoid redundant case checked in previous loop, and avoid self testing, e.g. [1][1], [2][2], [3][3] test
          for (int InputPin = (OutputPin + 1); InputPin <= Total_number_of_pin; InputPin++) {
            //Check if the expected result is "closed case" listed in the array
            //Reading the elements in the FOR MODE Selector
            for (int k = 0; k < ELEMENTS(FOR_Close); k++) {

              if (FOR_Close[k][0] == OutputPin && FOR_Close[k][1] == InputPin) {
                expected_circuit_state = 1;
                break;
              } else {
                expected_circuit_state = 0;
              }
            }
            //Check if the expected result is "closed case" listed in the array
            //Reading the elements in the FOR MODE TBC Selector
            if (expected_circuit_state == 0) {
              switch (j) {
                case 0:  //Reading Max Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Brake_Max_Close); k++) {

                    if (Brake_Max_Close[k][0] == OutputPin && Brake_Max_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 1:  //Reading Min Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Brake_Min_Close); k++) {

                    if (Brake_Min_Close[k][0] == OutputPin && Brake_Min_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 2:  //Reading Coasting TBC Array
                  for (int k = 0; k < ELEMENTS(Coasting_Close); k++) {

                    if (Coasting_Close[k][0] == OutputPin && Coasting_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 3:  //Reading Min motor TBC Array
                  for (int k = 0; k < ELEMENTS(Motor_Min_Close); k++) {

                    if (Motor_Min_Close[k][0] == OutputPin && Motor_Min_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 4:  //Reading Max motor TBC Array
                  for (int k = 0; k < ELEMENTS(Motor_Max_Close); k++) {

                    if (Motor_Max_Close[k][0] == OutputPin && Motor_Max_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 5:  //Reading Em Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Em_Brake_Close); k++) {

                    if (Em_Brake_Close[k][0] == OutputPin && Em_Brake_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
              }
            }
            t1 = millis();
            Serial.print(t1 / 1000);
            Serial.print(", ");
            Serial.print(Mode_Selector);
            Serial.print(", ");
            Serial.print(TBC_Selector);
            Serial.print(", ");
            IO_pin_handling(OutputPin, InputPin, expected_circuit_state);
          }
          Reset_pin_mode(OutputPin);
        }
      }
    }

    //Reading "SB" Modes with TBC combination
    else if (ModeSelector[i] == "SB") {
      //TBC mode selector
      for (int j = 0; j < ELEMENTS(TBCSelector); j++) {
        Mode_Selector = ModeSelector[i];
        TBC_Selector = TBCSelector[j];

        Serial.print("Testing in ");
        Serial.print(Mode_Selector);
        Serial.print(TBC_Selector);
        Serial.print(" mode will start in 10s");
        Serial.println(",");
        delay(10000);
        Serial.print("Testing in ");
        Serial.print(Mode_Selector);
        Serial.print(TBC_Selector);
        Serial.print(" mode started");
        Serial.println(",");
        delay(1000);

        //assigning input and output to Traction Brake Controller pins by using for loop and test for SB mode output
        for (int OutputPin = 1; OutputPin <= Total_number_of_pin; OutputPin++) {
          //Avoid redundant case checked in previous loop, and avoid self testing, e.g. [1][1], [2][2], [3][3] test
          for (int InputPin = (OutputPin + 1); InputPin <= Total_number_of_pin; InputPin++) {
            //Check if the expected result is "closed case" listed in the array
            //Reading the elements in the SB MODE Selector
            for (int k = 0; k < ELEMENTS(SB_Close); k++) {

              if (SB_Close[k][0] == OutputPin && SB_Close[k][1] == InputPin) {
                expected_circuit_state = 1;
                break;
              } else {
                expected_circuit_state = 0;
              }
            }
            //Check if the expected result is "closed case" listed in the array
            //Reading the elements in the SB MODE TBC Selector
            if (expected_circuit_state == 0) {
              switch (j) {
                case 0:  //Reading Max Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Brake_Max_Close); k++) {

                    if (Brake_Max_Close[k][0] == OutputPin && Brake_Max_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 1:  //Reading Min Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Brake_Min_Close); k++) {

                    if (Brake_Min_Close[k][0] == OutputPin && Brake_Min_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 2:  //Reading Coasting TBC Array
                  for (int k = 0; k < ELEMENTS(Coasting_Close); k++) {

                    if (Coasting_Close[k][0] == OutputPin && Coasting_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 3:  //Reading Min motor TBC Array
                  for (int k = 0; k < ELEMENTS(Motor_Min_Close); k++) {

                    if (Motor_Min_Close[k][0] == OutputPin && Motor_Min_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 4:  //Reading Max motor TBC Array
                  for (int k = 0; k < ELEMENTS(Motor_Max_Close); k++) {

                    if (Motor_Max_Close[k][0] == OutputPin && Motor_Max_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 5:  //Reading Em Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Em_Brake_Close); k++) {

                    if (Em_Brake_Close[k][0] == OutputPin && Em_Brake_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
              }
            }
            t1 = millis();
            Serial.print(t1 / 1000);
            Serial.print(", ");
            Serial.print(Mode_Selector);
            Serial.print(", ");
            Serial.print(TBC_Selector);
            Serial.print(", ");
            IO_pin_handling(OutputPin, InputPin, expected_circuit_state);
          }
          Reset_pin_mode(OutputPin);
        }
      }
    }

    //Reading "REV" Modes with TBC combination
    else if (ModeSelector[i] == "REV") {
      //TBC mode selector
      for (int j = 0; j < ELEMENTS(TBCSelector); j++) {
        Mode_Selector = ModeSelector[i];
        TBC_Selector = TBCSelector[j];

        Serial.print("Testing in ");
        Serial.print(Mode_Selector);
        Serial.print(TBC_Selector);
        Serial.print(" mode will start in 10s");
        Serial.println(",");
        delay(10000);
        Serial.print("Testing in ");
        Serial.print(Mode_Selector);
        Serial.print(TBC_Selector);
        Serial.print(" mode started");
        Serial.println(",");
        delay(1000);

        //assigning input and output to Traction Brake Controller pins by using for loop and test for REV mode output
        for (int OutputPin = 1; OutputPin <= Total_number_of_pin; OutputPin++) {
          //Avoid redundant case checked in previous loop, and avoid self testing, e.g. [1][1], [2][2], [3][3] test
          for (int InputPin = (OutputPin + 1); InputPin <= Total_number_of_pin; InputPin++) {
            //Check if the expected result is "closed case" listed in the array
            //Reading the elements in the REV MODE Selector
            for (int k = 0; k < ELEMENTS(REV_Close); k++) {

              if (REV_Close[k][0] == OutputPin && REV_Close[k][1] == InputPin) {
                expected_circuit_state = 1;
                break;
              } else {
                expected_circuit_state = 0;
              }
            }
            //Check if the expected result is "closed case" listed in the array
            //Reading the elements in the REV MODE TBC Selector
            if (expected_circuit_state == 0) {
              switch (j) {
                case 0:  //Reading Max Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Brake_Max_Close); k++) {

                    if (Brake_Max_Close[k][0] == OutputPin && Brake_Max_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 1:  //Reading Min Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Brake_Min_Close); k++) {

                    if (Brake_Min_Close[k][0] == OutputPin && Brake_Min_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 2:  //Reading Coasting TBC Array
                  for (int k = 0; k < ELEMENTS(Coasting_Close); k++) {

                    if (Coasting_Close[k][0] == OutputPin && Coasting_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 3:  //Reading Min motor TBC Array
                  for (int k = 0; k < ELEMENTS(Motor_Min_Close); k++) {

                    if (Motor_Min_Close[k][0] == OutputPin && Motor_Min_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 4:  //Reading Max motor TBC Array
                  for (int k = 0; k < ELEMENTS(Motor_Max_Close); k++) {

                    if (Motor_Max_Close[k][0] == OutputPin && Motor_Max_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
                case 5:  //Reading Em Brake TBC Array
                  for (int k = 0; k < ELEMENTS(Em_Brake_Close); k++) {

                    if (Em_Brake_Close[k][0] == OutputPin && Em_Brake_Close[k][1] == InputPin) {
                      expected_circuit_state = 1;
                      break;
                    } else {
                      expected_circuit_state = 0;
                    }
                  }
                  break;
              }
            }
            t1 = millis();
            Serial.print(t1 / 1000);
            Serial.print(", ");
            Serial.print(Mode_Selector);
            Serial.print(", ");
            Serial.print(TBC_Selector);
            Serial.print(", ");
            IO_pin_handling(OutputPin, InputPin, expected_circuit_state);
          }
          Reset_pin_mode(OutputPin);
        }
      }
    }
  }
  delay(1000);
  exit(0);
}
