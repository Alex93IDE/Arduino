#include "Timer_3.h"

unsigned int x;
int flag = 0;

void setup()
{
  init_timer_3();
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

boolean led = false;

// Código que ejecutamos en cada interrupción
ISR(TIMER3_COMPA_vect)
{
  TIFR3 = 0;
  TCNT3 = 0;
  OCR3A = 12499; //50ms
  x++;
  if (x == 20){
    flag = 1;
    x = 0;
  }
}

void loop()
{
  if (flag)
  {
    Serial.println("hola");
    if (led)
    {
      digitalWrite(13, LOW);
      led = false;
    }
    else
    {
      digitalWrite(13, HIGH);
      led = true;
    }
    flag = 0;
  }
}
