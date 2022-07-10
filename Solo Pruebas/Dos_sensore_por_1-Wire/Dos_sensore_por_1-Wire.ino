#include <TimerOne.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int pin = 9;

OneWire objeto(pin);
DallasTemperature sensor(&objeto);

DeviceAddress Temperatura = {0x28, 0xFF, 0xC5, 0xF9, 0x8B, 0x16, 0x03, 0x5D};
//DeviceAddress IButton = {0x01, 0x50, 0x40, 0xA7, 0x01, 0x00, 0x00, 0x7E};

byte addr[8];
String keyEstado = "";
String serie = "01a74050";
int timer;
bool sonda = 0;
bool ibutton = 0;
int led =0;

void setup()
{
  Serial.begin(9600);
  sensor.begin();
  pinMode(13, OUTPUT);
  sensor.setResolution(Temperatura, 10);
  Timer1.initialize(15000);
  Timer1.attachInterrupt(Tiempo);
}

void loop()
{
  if (sonda == 1)
  {
    SondaTemp();
    sonda = 0;
  }
  if (ibutton == 1)
  {
    iButtonnnresive();
    ibutton = 0;
  }
 if(led==1)
  {
    digitalWrite(13,HIGH);
  }
  if(led==2)
  {
    digitalWrite(13,LOW);
    led=0;
  }
  
  
}

void Tiempo()
{
  if (timer == 0)
  {
    sonda = 1;
  }
  if (timer == 1)
  {
    ibutton = 1;
  }
  timer += 1;

  if (timer == 2)
  {
    timer = 0;
  }
}

void SondaTemp()
{
  sensor.requestTemperatures();   // se manda comandos para la toma de temp al sensor
  Serial.print(sensor.getTempC(Temperatura),1); //lectura y muestreo
  Serial.println("ºC");
}

void iButtonnnresive()
{
  getKeyCode();
  if (keyEstado == "ok")
  {
    byte i;
    String temporal = "";
    for ( i = 5; i > 0; i--)
    {
      Serial.print(addr[i], HEX);
      temporal += String(addr[i], HEX);
    }
    if (temporal == serie)  //Otra forma de preguntar igualdad (temporal.equals(serie))
    {
      led+=1;
    }

  }
  else if (keyEstado != "")
  {
    //Serial.println(keyEstado);
  }
}

void getKeyCode()
{
  byte present = 0;
  byte data[12];
  keyEstado = "";

  if ( !objeto.search(addr))
  {
    objeto.reset_search();
    return;
  }
  if ( OneWire::crc8( addr, 7) != addr[7])
  {
    keyEstado = "CRC invalid";
    return;
  }

  if ( addr[0] != 0x01)
  {
    keyEstado = "not DS1990A";
    return;
  }
  keyEstado = "ok";
  objeto.reset();
}



 
