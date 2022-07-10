#include <SoftwareSerial.h>

SoftwareSerial BT1(7, 8); // RX | TX
char txt;

void setup()
{
  Serial.begin(9600);
  Serial.println("HOLA");
  BT1.begin(38400);
}
void loop()
{ 

  if (Serial.available())
  { txt = Serial.read();
    BT1.print(txt);
  }
  if (BT1.available()){
   txt = BT1.read();
    Serial.print(txt);
  }
}
