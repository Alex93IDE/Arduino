#ifndef TIMER_3_H
#define TIMER_3_H

#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "pins_arduino.h"
/*
   ISR(TIMER3_COMPA_vect){
     TIFR3 = 0;
	 OCR3A = 12499;
	 TCNT3 = 0;
   }
   Poner esta funcion en el .ino, que es la interrupcion del Timer 2
*/
void init_timer_3();
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void init_timer_3()
{
  cli();
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;
  OCR3A = 12499; //50ms
  TCCR3B = 0b00001011; //pre-escaler 64, CTC Mode
  TCNT3 = 53036;
  TIMSK3 = (TIMSK3 | 0b00000010);
  TIFR3 = 0b00000000;
  sei();
}

#endif
