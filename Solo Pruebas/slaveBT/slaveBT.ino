/*
This code is in the public domain.
written by Itamar Eduardo Gonçalves de Oliveira
*/

#include <SoftwareSerial.h>
#define bt_power 12
#define bt_key_power 9
#define led 2

SoftwareSerial BT(11, 10); // RX | TX

void setup()
{
  // set the pins to OUTPUT
  pinMode(bt_power, OUTPUT);  
  pinMode(bt_key_power, OUTPUT);
  pinMode(led, OUTPUT);
  
  // set the pins to LOW
  digitalWrite(bt_power, LOW);
  digitalWrite(bt_key_power, LOW);
  
  /************************************************
  Setting the pins to low is important because 
  in order for us to get into AT mode the key pin
  has to be set to Ground FIRST. Many tutorials out
  there fail to mention this important fact and 
  therefore many people have problems with getting 
  into the AT mode of the HC-05
  ************************************************/
  
  // make sure the key has been LOW for a bit
  delay(100);
  
  // set the key pin to High
  digitalWrite(bt_key_power, HIGH);
  
  // small delay
  delay(100);
  
  // now power on the BT
  digitalWrite(bt_power, HIGH);
  
  // start our serial so we can send and recieve
  // information from the BT module
  Serial.begin(9600);
  // initiate the BT serial at 38400 which is the default 
  // speed at which the BT AT mode operates at
  BT.begin(38400);
  
  // self explanatory
  Serial.write("For a list of commands, visit: \n");
  Serial.write("Type AT commands  \n\n");
  
  // Send an "AT" command to the AT (without quotes)
  // if response is OK, then we are connected
  // and ready to program the BT module
  delay(3000);
  BT.write("AT+ROLE=0\r\n");
  Serial.write("AT+ROLE=0\r\n");
  delay(1000);
  BT.write("AT+CMODE=1\r\n");
  Serial.write("AT+CMODE=1\r\n");
  delay(1000);
  BT.write("AT+INIT\r\n");
  Serial.write("AT+INIT\r\n");
  delay(3000);
  BT.write("AT+INQ\r\n");
  Serial.write("AT+INQ\r\n");
  delay(3000);   
 }

void loop()
{

  // listen for a response from the HC-05 and write it to the serial monitor
  if (BT.available()){
      char te = BT.read();
      Serial.write(te);
      if(te=='a'){
        digitalWrite(led,HIGH);
      }
      else if(te=='b'){
        digitalWrite(led,LOW);
      }
  }

  // listen for user input and send it to the HC-05
  if (Serial.available())
    BT.write(Serial.read());
    
}
