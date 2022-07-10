#include "UnoJoy.h"


void setup() {
  // put your setup code here, to run once:
  setupPins();
  setupUnoJoy();
}

void loop() {
  // put your main code here, to run repeatedly:
 dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins
  for (int i = 2; i <= 12; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

dataForController_t getControllerData(void){
  
  
  dataForController_t controllerData = getBlankDataForController();
 
    controllerData.triangleOn = !digitalRead(6);
 
    controllerData.squareOn = !digitalRead(7);
 
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use  
  controllerData.leftStickX = analogRead(A0) >> 2;
  controllerData.leftStickY = analogRead(A1) >> 2;
  
  //controllerData.rightStickY = analogRead(A3) >> 2;
  // And return the data!
  return controllerData;
}
