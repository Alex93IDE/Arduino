#ifndef TECLADO_H
#define TECLADO_H
#include <Arduino.h>

#define pin_key_menu 2
#define KEY_ON LOW
#define KEY_OFF HIGH

char tecla = 'N';
char tecla_actual = 'N';
char tecla_anterior = 'N';
char tecla_repeticiones = 0;

char getTecla();
void buscarTeclaArduino();
void inicializar_puertos_teclado();
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void inicializar_puertos_teclado()
{
  pinMode(pin_key_menu, INPUT);
}

char getTecla()
{

  if (digitalRead(pin_key_menu) == KEY_ON)
  {
    return 'M';
  }
  return 'N';
}

void buscarTeclaArduino()
{
  tecla = getTecla();
  /*if (tecla_anterior == tecla_actual)
  {
    tecla = tecla_actual;
    tecla_anterior = tecla_actual;
    tecla_actual = 'N';
    tecla_repeticiones++;
  }
  else
  {
    tecla_anterior = tecla_actual;
    tecla_repeticiones = 0;
  }*/
}
#endif
