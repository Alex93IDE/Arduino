#include <OneWire.h>
#include <DallasTemperature.h>

const int pin = 9; //pin donde se conecta el bus onewire

OneWire objeto(pin);
DallasTemperature sensor(&objeto);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
sensor.begin();
}

void loop() {
 sensor.requestTemperatures();   // se manda comandos para la toma de temp al sensor
 Serial.print(sensor.getTempCByIndex(0),1); //lectura y muestreo
 Serial.println("ºC");
 delay(2500);
 

}
