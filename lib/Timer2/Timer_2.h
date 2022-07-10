#ifndef TIMER_2_H
#define TIMER_2_H
/*
 * ISR(TIMER2_OVF_vect){} 
 * Poner esta funcion en el .ino, que es la interrupcion del Timer 2
*/

class Timer_2
{
private:
    /* data */
public:
    Timer_2(/* args */);
    ~Timer_2();
    void init_timer_2();
};

#endif
