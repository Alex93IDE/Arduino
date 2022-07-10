#include <VirtualWire.h>
#include <avr/wdt.h>

const int dataPin = 9;
const int ledPin = 13;
const int sensorPin = 8;
const int sensorPin_2 = 7;

char msg[4] = {'E', '\0'};
char msg2[4] = {'A', '\0'};
int estado = 1;
int estado_2 = 1;

void estado_puerta();
void envio_de_trama();

void setup()
{
  vw_setup(2400);
  vw_set_tx_pin(dataPin);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(sensorPin_2, INPUT_PULLUP);
  Serial.begin(9600);

  wdt_disable();
  wdt_enable(WDTO_2S);
}

void loop()
{
  Serial.println(estado);
  estado_puerta();
  envio_de_trama();
  wdt_reset();
}

void estado_puerta()
{
  estado = digitalRead(sensorPin);
  estado_2 = digitalRead(sensorPin_2);
}

void envio_de_trama()
{

  if (estado == 0)
  {
    vw_send((uint8_t *)msg2, strlen(msg2));   //A
    vw_wait_tx();
    digitalWrite(ledPin, LOW);
  }
  else if (estado == 1)
  {
    vw_send((uint8_t *)msg, strlen(msg));  //E
    vw_wait_tx();
    digitalWrite(ledPin, HIGH);
  }
}
