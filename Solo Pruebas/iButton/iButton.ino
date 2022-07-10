#include <OneWire.h>

OneWire  ds(9);

byte addr[8];
String keyStatus = "";
String serie = "01a74050";
void setup(void) {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}
void loop(void) {
  getKeyCode();
  if (keyStatus == "ok")
  {
    byte i;
    String temporal = "";
    for ( i = 5; i > 0; i--)
    {  
        Serial.print(addr[i],HEX);
        temporal += String(addr[i],HEX);
    }
    if (temporal==serie)    //Otra forma de preguntar igualdad (temporal.equals(serie))
    {
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
    }
    
  }
  else if (keyStatus != "") 
  {
    Serial.println(keyStatus);
  }
 
  delay(460);
}



void getKeyCode() {
  byte present = 0;
  byte data[12];
  keyStatus = "";

  if ( !ds.search(addr)) {
    ds.reset_search();
    return;
  }
  if ( OneWire::crc8( addr, 7) != addr[7]) {
    keyStatus = "CRC invalid";
    return;
  }

  if ( addr[0] != 0x01) {
    keyStatus = "not DS1990A";
    return;
  }
  keyStatus = "ok";
  ds.reset();
}

