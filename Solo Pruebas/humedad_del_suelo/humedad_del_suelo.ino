
int valor;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 valor = analogRead(A1);
 Serial.println(valor);
}
