#include <Wire.h>

int ADXL345 = 0x53; //direccion del sensor para i2c
float X,Y,Z;
float roll,pitch;
float rollF,pitchF;

void setup() {
  Serial.begin(19200);
  Wire.begin();
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D); //// acceder al registro de control powwer_ctl registro 2d
  Wire.write(8); // 0000 1000 bit D3 // es poner en 1 al D3 //Buscar el dataSheett
  Wire.endTransmission();
  delay(10);

  // off-set Calibracion
  //X
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1E);
  Wire.write(-3);
  Wire.endTransmission();
  delay(10);
  //y
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1F);
  Wire.write(1);
  Wire.endTransmission();
  delay(10);
  //Z es 0x20
}

void loop() {
  // put your main code here, to run repeatedly:
Wire.beginTransmission(ADXL345);
Wire.write(0x32); 
Wire.endTransmission(false);
Wire.requestFrom(ADXL345, 6, true); //leer 6 registro en total
X = Wire.read() | (Wire.read() << 8);
X = X / 256;
Y = Wire.read() | (Wire.read() << 8);
Y = Y / 256;
Z = Wire.read() | (Wire.read() << 8);
Z = Z / 256;
delay(200);
//Calculando el Roll and Pitch(rotacion de los 2 ejes 'x' y 'y'  )
//Creo que es angulo
roll = atan(Y / sqrt(pow(X,2)+pow(Z,2))) * 180/3.14;  //es la inclinacion en el eje y pero gira en el eje x
pitch = atan(X/sqrt(pow(Y,2)+pow(Z,2))) *180/3.14;   //es la inclinacion en el eje x pero gira sobre el eje y

// Filtro pasa-bajo
rollF = 0.94 * rollF + 0.06 * roll;
pitchF = 0.94 * pitchF + 0.06 * pitch;

//Serial.print("X= ");
//Serial.print(X);
//Serial.print("     Y= ");
//Serial.print(Y);
//Serial.print("     Z=");
//Serial.println(Z);
Serial.print("roll= ");
Serial.print(rollF);
Serial.print("//");
Serial.println(pitchF);
}
