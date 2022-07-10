#ifndef PANTALLAS_H
#define PANTALLAS_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <stdio.h>
#include "teclado_normal.h"
#include "trabajo.h"

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

#define PANTALLA_PRINCIPAL 0
#define PANTALLA_TRABAJO 1
#define PANTALLA_TRABAJO_2 2

uint8_t temp[8] = {0b00100, 0b01010, 0b01010, 0b01110, 0b01110, 0b11111, 0b11111, 0b01110};
uint8_t grado[8] = {0b01110, 0b01010, 0b01110, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000};
uint8_t punto[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b01110, 0b01110, 0b01110};
byte LT[8] = {B01111, B11111, B11111, B11111, B11111, B11111, B11111, B11111};
byte UB[8] = {B11111, B11111, B11111, B00000, B00000, B00000, B00000, B00000};
byte RT[8] = {B11110, B11111, B11111, B11111, B11111, B11111, B11111, B11111};
byte LL[8] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B01111};
byte LB[8] = {B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111};
byte LR[8] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11110};
byte UMB[8] = {B11111, B11111, B11111, B00000, B00000, B00000, B11111, B11111};
byte LMB[8] = {B11111, B00000, B00000, B00000, B00000, B11111, B11111, B11111};

int x, numero;
int pantalla;
char mostrar_pantallas();
void pantallaPrincipal();
char _pantallaPrincipal();
void mostrarNumero();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void custom0() // Seleciona os segmentos para formar o numero 0
{
  lcd.setCursor(x, 0); // Seleciona a linha superior
  lcd.write((byte)0);  // Segmento 0 selecionado
  lcd.write(1);        // Segmento 1 selecionado
  lcd.write(2);
  lcd.setCursor(x, 1); // Seleciona a linha inferior
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
}
void custom1() // Seleciona os segmentos para formar o numero 1
{
  lcd.setCursor(x + 1, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x + 2, 1);
  lcd.write(5);
}
void custom2() // Seleciona os segmentos para formar o numero 2
{
  lcd.setCursor(x, 0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(7);
}
void custom3() // Seleciona os segmentos para formar o numero 3
{
  lcd.setCursor(x, 0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}
void custom4() // Seleciona os segmentos para formar o numero 4
{
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(x + 2, 1);
  lcd.write(5);
}
void custom5() // Seleciona os segmentos para formar o numero 5
{
  lcd.setCursor(x, 0);
  lcd.write((byte)0);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}
void custom6() // Seleciona os segmentos para formar o numero 6
{
  lcd.setCursor(x, 0);
  lcd.write((byte)0);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}
void custom7() // Seleciona os segmentos para formar o numero 7
{
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x + 1, 1);
  lcd.write((byte)0);
}
void custom8() // Seleciona os segmentos para formar o numero 8
{
  lcd.setCursor(x, 0);
  lcd.write((byte)0);
  lcd.write((byte)6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}
void custom9() // Seleciona os segmentos para formar o numero 9
{
  lcd.setCursor(x, 0);
  lcd.write((byte)0);
  lcd.write((byte)6);
  lcd.write((byte)2);
  lcd.setCursor(x + 2, 1);
  lcd.write((byte)5);
}

void mostraKM(int km)
{
  lcd.clear();
  // 3ro
  x = 8;
  numero = km % 10;
  mostrarNumero();
  // 2do
  if (km >= 10)
  {
    x = 5;
    numero = km / 10;
    numero = numero % 10;
    mostrarNumero();
  }
  // 1er
  if (km >= 100)
  {
    x = 2;
    numero = km / 100;
    mostrarNumero();
  }
}

void mostrarNumero()
{
  switch (numero)
  {
  case 0:
    custom0();
    break;
  case 1:
    custom1();
    break;
  case 2:
    custom2();
    break;
  case 3:
    custom3();
    break;
  case 4:
    custom4();
    break;
  case 5:
    custom5();
    break;
  case 6:
    custom6();
    break;
  case 7:
    custom7();
    break;
  case 8:
    custom8();
    break;
  case 9:
    custom9();
    break;
  }
}

void pantallaPrincipal()
{
  mostraKM(km_h);
  lcd.setCursor(11, 1);
  lcd.print(" KM/H");
  lcd.setCursor(0, 2);
  lcd.print(tecla);
  lcd.print(digitalRead(2));
  lcd.setCursor(0, 3);
  lcd.print("T:");
  lcd.print(temperatura, 1);
  lcd.setCursor(8, 3);
  if (km_recorridos < 100000)
  {
    lcd.print("0");
    if (km_recorridos < 10000)
    {
      lcd.print("0");
      if (km_recorridos < 1000)
      {
        lcd.print("0");
        if (km_recorridos < 100)
        {
          lcd.print("0");
          if (km_recorridos < 10)
          {
            lcd.print("0");
          }
        }
      }
    }
  }
  lcd.print(km_recorridos, 1);
  pantalla = PANTALLA_TRABAJO;
}

void pantallaPrincipal_2()
{

  lcd.setCursor(8, 0);
  if (mi_gps.horagps.hora < 10)
  {
    lcd.print("0");
  }
  lcd.print(mi_gps.horagps.hora);
  lcd.print(":");
  if (mi_gps.horagps.minuto < 10)
  {
    lcd.print("0");
  }
  lcd.print(mi_gps.horagps.minuto);
  lcd.print(":");
  if (mi_gps.horagps.segundo < 10)
  {
    lcd.print("0");
  }
  lcd.print(mi_gps.horagps.segundo);
  lcd.setCursor(8, 1);
  if (mi_gps.horagps.dia < 10)
  {
    lcd.print("0");
  }
  lcd.print(mi_gps.horagps.dia);
  lcd.print("/");
  if (mi_gps.horagps.mes < 10)
  {
    lcd.print("0");
  }
  lcd.print(mi_gps.horagps.mes);
  lcd.print("/");
  lcd.print(mi_gps.horagps.anno);
  lcd.setCursor(0, 2);
  lcd.print(tecla);
  lcd.print(digitalRead(2));
  pantalla = PANTALLA_TRABAJO_2;
}

char _pantallaPrincipal()
{
  if (pantalla == PANTALLA_TRABAJO)
  {
    pantallaPrincipal();
    switch (tecla)
    {
    case 'M':
      lcd.clear();
      pantallaPrincipal_2();
      return 1;
    }
    return 1;
  }
  return 0;
}

char _pantallaPrincipal_2()
{
  if (pantalla == PANTALLA_TRABAJO_2)
  {
    pantallaPrincipal_2();
    switch (tecla)
    {
    case 'M':
      lcd.clear();
      pantallaPrincipal();
      return 1;
    }
    return 1;
  }
  return 0;
}

char mostrar_pantallas()
{
  if (_pantallaPrincipal())
    return 1;
  if (_pantallaPrincipal_2())
    return 1;
  return 0;
}

#endif
