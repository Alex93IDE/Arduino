#include "Timer_2.h"

Timer_2 mi_timer2;
unsigned int x;
int flag = 0;

void setup()
{
  // put your setup code here, to run once:
  mi_timer2.init_timer_2();
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (flag)
  {
    flag = 0;
    Serial.println("hola");
    if (digitalRead(13) == LOW)
    {
      digitalWrite(13, HIGH);
    }
    else
    {
      digitalWrite(13, LOW);
    }
  }
}

ISR(TIMER2_COMPA_vect)
{
  TIFR2 = 0b00000000;
  OCR2A = 155;
  TCNT2 = 0; 
  x++;
  if (x == 100)
  {
    flag = 1;
    x = 0;
  }
}
