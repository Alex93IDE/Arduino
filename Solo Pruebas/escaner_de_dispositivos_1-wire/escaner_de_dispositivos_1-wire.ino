#include <OneWire.h>

const int pin = 11,12,13,10;

OneWire objeto(pin);


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
escanerdispositivos();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void escanerdispositivos(void)
{
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  Serial.println("Buscando dispositivos 1-Wire");
  while(objeto.search(addr)) {
    Serial.println("Encontrado dispositivo 1-Wire en direccion");
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("Error en dispositivo, CRC invalido!\n");
        return;
    }
  }
  Serial.println("Búsqueda finalizada");
  objeto.reset_search();
  return;
}
