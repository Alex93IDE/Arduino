
void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT);
  pinMode(13,OUTPUT);
Serial.begin(9600);
}

void loop() {
  
int valor,valor1,valor2 = 0;
for(int i = 0;i<30;i++ )
{
  valor+= analogRead(8);
}
valor1 = valor/30;
valor2 = valor/30;
valor = max(valor1,valor2);
double temp = Termistor(valor);
 Serial.println(temp);
 delay(500);
}

double Termistor(int muestra)
{
  double Temp;
  Temp = log(10000.0 * ((1024.0 / muestra-2)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
  Temp = Temp - 273.15; //Kelvin a Celcius
  return Temp;
}
