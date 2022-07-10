
#include <avr/wdt.h>
#include "src/pantallas.h"
#include "src/trabajo.h"
#include <Timer3.h>

int timer_50ms;
int timer_100ms;
int timer_200ms;
int timer_250ms;
int timer_500ms;
int timer_1s;

bool flag_50ms = 0;
bool flag_500ms = 0;
bool flag_200ms = 0;
bool flag_250ms = 0;
bool flag_100ms = 0;
bool flag_1s = 0;

const int pin_led_test = 31;

void rxRead()
{
  char c;
  if (Serial1.available() > 0)
  {
    c = Serial1.read();
    mi_gps.agregando_buffer_gps(c);
    Serial.print(c);
  }
}
void setup()
{
  // put your setup code here, to run once:
  noInterrupts();
  init_timer_3();
  inicializar_puertos_teclado();
  lcd.begin(16, 4); // Inicializando la LCD
  lcd.createChar(0, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);
  pantalla = PANTALLA_TRABAJO;
  Serial.begin(9600);
  Serial1.begin(9600); // GPS
  attachInterrupt(digitalPinToInterrupt(19), rxRead, RISING);
  sensor.begin();
  interrupts();
  // wdt_disable(); // desabilita el perro guardian mientras se configura
  // wdt_enable(WDTO_2S);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (flag_50ms)
  {

    flag_50ms = 0;
  }
  if (flag_100ms)
  {

    flag_100ms = 0;
  }
  if (flag_200ms)
  {
    mostrar_pantallas();
    flag_200ms = 0;
  }
  if (flag_250ms)
  {

    flag_250ms = 0;
  }
  if (flag_500ms == 1)
  {
    calculo_temperatura();
    mi_gps.decodificar_trama_gps();
    mi_gps.convirtiendo_trama_gps();
    flag_500ms = 0;
  }
  if (flag_1s == 1)
  {
    led_test(pin_led_test);
    mi_gps.cargar_reloj_GPS();
    calculo_de_odometro_km_h();
    flag_1s = 0;
    //Serial.println("Hola");
  }
  buscarTeclaArduino();
  // wdt_reset();
}

ISR(TIMER3_COMPA_vect)
{
  TIFR3 = 0;
  TCNT3 = 0;
  OCR3A = 12502; // 50ms
  flag_50ms = 1;
  timer_100ms++;
  timer_200ms++;
  timer_250ms++;
  timer_500ms++;
  timer_1s++;
  if (timer_100ms >= 2)
  {
    flag_100ms = 1;
    timer_100ms = 0;
  }
  if (timer_200ms >= 4)
  {
    flag_200ms = 1;
    timer_200ms = 0;
  }
  if (timer_250ms >= 5)
  {
    flag_250ms = 1;
    timer_250ms = 0;
  }
  if (timer_500ms >= 10)
  {
    flag_500ms = 1;
    timer_500ms = 0;
  }
  if (timer_1s >= 20)
  {
    flag_1s = 1;
    timer_1s = 0;
  }
}
