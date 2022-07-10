#ifndef TRABAJO_H
#define TRABAJO_H

#include <Arduino.h>
#include <gps.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define VERSION 1.0
#define FECHA __DATE__

const int pin_sensor_temp = 30; // pin donde se conecta el bus onewire
float km_h = 0;
double km_recorridos;
boolean estado = false;
float temperatura = 0;

OneWire objeto(pin_sensor_temp);
DallasTemperature sensor(&objeto);

void led_test(int);
void calculo_de_odometro_km_h();
void calculo_temperatura();
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void led_test(int pin)
{
    digitalWrite(pin, estado);
    estado = !estado;
}

void calculo_de_odometro_km_h()
{
    km_h = mi_gps.velocidad * 3.6;
    if (km_h >= 5)
    {
        km_recorridos += mi_gps.velocidad * 0.001;
    }
    else
    {
        km_h = 0;
    }
}

void calculo_temperatura()
{
    sensor.requestTemperatures();
    temperatura = sensor.getTempCByIndex(0);
}

#endif
