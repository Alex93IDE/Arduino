#include "Timer_2.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "pins_arduino.h"

Timer_2::Timer_2(/* args */)
{
}

Timer_2::~Timer_2()
{
}

void Timer_2::init_timer_2()
{
    cli();
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
    OCR2A = 155;
    TIMSK2 = (TIMSK2 | 0b00000010);
    TCCR2A = 0b00000010;
    TCCR2B = 0b00000111;
    TCNT2 = 100;  
    TIFR2 = 0b00000000;
    sei();
}

///tiene un pequeno error no son 10ms son 9.849ms
