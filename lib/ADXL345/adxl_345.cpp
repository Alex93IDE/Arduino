#include <Arduino.h>
#include "adxl_345.h"

Acelerometro mi_adxl;

Acelerometro::Acelerometro()
{
}

void Acelerometro::init_acelerometro(int direccion, char registro, char valor)
{
    Wire.begin();
    Wire.beginTransmission(direccion);
    Wire.write(registro);
    Wire.write(valor);
    Wire.endTransmission();
}

void Acelerometro::ajuste_off_set(int direccion, char registro_X, char valor_X,
                                  char registro_Y, char valor_Y, char registro_Z, char valor_Z)
{ //x
    Wire.beginTransmission(direccion);
    Wire.write(registro_X);
    Wire.write(valor_X);
    Wire.endTransmission();
    delay(10);
    //y
    Wire.beginTransmission(direccion);
    Wire.write(registro_Y);
    Wire.write(valor_Y);
    Wire.endTransmission();
    delay(10);
    //z
    Wire.beginTransmission(direccion);
    Wire.write(registro_Z);
    Wire.write(valor_Z);
    Wire.endTransmission();
    delay(10);
}

void Acelerometro::realizar_lectura(int direccion, char registro, char cantidad_bytes)
{
    Wire.beginTransmission(direccion);
    Wire.write(registro);
    Wire.endTransmission(false);
    Wire.requestFrom(direccion, cantidad_bytes, true); //leer 6 registro en total
    valor_x = Wire.read() | (Wire.read() << 8);
    x_out = valor_x / 256;
    valor_y = Wire.read() | (Wire.read() << 8);
    y_out = valor_y / 256;
    valor_z = Wire.read() | (Wire.read() << 8);
    z_out = valor_z / 256;
}

void Acelerometro::calcular_angulos()
{
    roll = atan(y_out / sqrt(pow(x_out, 2) + pow(z_out, 2))) * 180 / 3.14;  // 180* pi es para llevar de radines a angulo
    pitch = atan(-1 * x_out / sqrt(pow(y_out, 2) + pow(z_out, 2))) * 180 / 3.14;

    // Filtro pasa-bajo
    roll_F = 0.94 * roll_F + 0.06 * roll;
    pitch_F = 0.94 * pitch_F + 0.06 * pitch;
}