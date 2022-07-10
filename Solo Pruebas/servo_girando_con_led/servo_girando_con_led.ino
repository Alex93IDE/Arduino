/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
const int led1 = 2;
const int led2 = 13;

void setup() {
  myservo.attach(9); 
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}

void loop() {
  for (pos = 0; pos <= 180; pos ++) {
    // in steps of 1 degree
    myservo.write(pos);
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    delay(15);                     
  }
  for (pos = 180; pos >= 0; pos --) { 
    myservo.write(pos); 
    digitalWrite(led1,LOW); 
    digitalWrite(led2,HIGH);
    delay(15);             
  }
}



