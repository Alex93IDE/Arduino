
float frecuencia = 0;
float muestra1, muestra2 = 0;

void setup()
{ 
  Serial.begin(2000000);
}

void loop()
{
  muestra1 = pulseIn(A1, HIGH);
  muestra1 = 1 / muestra1 * 1000000 ;
  muestra2 = pulseIn(A1, HIGH);
  muestra2 = 1 / muestra2 * 1000000 ;
  frecuencia = min(muestra1, muestra2)/2;
  Serial.print(frecuencia, 2);
  Serial.println(" Hz  ");
  delay(997);
}




