#ifndef TECLADO_H
#define TECLADO_H
#include <Arduino.h>

#define pin_key_menu 13
#define pin_key_salir 10
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
  pinMode(pin_key_salir, INPUT);
}

char getTecla()
{

  if (digitalRead(pin_key_menu) == KEY_ON &&
      digitalRead(pin_key_salir) == KEY_OFF)
  {
    return 'M';
  }
  if (digitalRead(pin_key_menu) == KEY_OFF &&
      digitalRead(pin_key_salir) == KEY_ON)
  {
    return 'S';
  }
  return 'N';
}

void buscarTeclaArduino()
{
  tecla_actual = getTecla();
  if (tecla_anterior == tecla_actual)
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
  }
}
#endif
