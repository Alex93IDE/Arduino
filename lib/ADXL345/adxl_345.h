#ifndef ADXL_345_H
#define ADXL_345_H
#include <Wire.h>

class Acelerometro
{
public:
    Acelerometro();
    
    float x_out, y_out, z_out;
    float roll_F, pitch_F;
    void init_acelerometro(int direccion, char registro, char valor);
    void ajuste_off_set(int direccion, char registro_X, char valor_X,
                        char registro_Y, char valor_Y, char registro_Z, char valor_Z);
    void realizar_lectura(int direccion, char registro, char cantidad_bytes);
    void calcular_angulos();

private:
    float valor_x, valor_y, valor_z;
    float roll, pitch;
};

extern Acelerometro mi_adxl;

#endif
