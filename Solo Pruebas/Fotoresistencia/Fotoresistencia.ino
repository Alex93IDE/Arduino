
int fotoresistencia_pin = A0;
int valor = 0;

void setup()
{
  // put your setup code here, to run once:
  pinMode(fotoresistencia_pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  valor = analogRead(fotoresistencia_pin);
 // Serial.print("LUX: ");
  Serial.println(valor);
  delay(1000);
}
