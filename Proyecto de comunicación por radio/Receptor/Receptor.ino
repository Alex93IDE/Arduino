#include <VirtualWire.h>
#include <avr/wdt.h>

const int dataPin = 9;
const int relePin = 8;
const int relePin_2 = 7;

uint8_t data;
uint8_t data_length = 1;
char x;

void setup()
{
  Serial.begin(9600);

  vw_setup(2400);
  vw_set_rx_pin(dataPin);
  vw_rx_start();
  pinMode(13, OUTPUT);
  pinMode(relePin, OUTPUT);
  pinMode(relePin_2, OUTPUT);
  digitalWrite(relePin, HIGH);
  wdt_disable();
  wdt_enable(WDTO_2S);
}

void loop()
{
  lectura_de_trama();
  wdt_reset();
}

void lectura_de_trama()
{
  if (vw_get_message(&data, &data_length))
  {
    if ((char)data == 'E')
    {
      digitalWrite(relePin_2, LOW);
      digitalWrite(relePin, LOW);
      digitalWrite(13, HIGH);
      Serial.println((char)data);
    }
    else if ((char)data == 'A')
    {
      digitalWrite(relePin_2, HIGH);
      digitalWrite(relePin, HIGH);
      digitalWrite(13, LOW);
      Serial.println((char)data);
    }
  }
}
