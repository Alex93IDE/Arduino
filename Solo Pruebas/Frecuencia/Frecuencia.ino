#include <TimerOne.h>

const int Pin = 13;
volatile int estado = LOW;

void setup()
{
  pinMode(Pin, OUTPUT);
  Timer1.initialize(200);  
  Timer1.attachInterrupt(Tiempo);
  Serial.begin(2000000);
}

void loop(void)
{
  Serial.println(estado);
}

void Tiempo()
{
  digitalWrite(Pin, estado); //max 54.4kHz
  estado =! estado;
}

