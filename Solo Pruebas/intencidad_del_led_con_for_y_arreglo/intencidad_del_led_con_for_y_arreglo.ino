


const int led = 13;
int arreglo[5] = {100, 5, 3, 200, 1};

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int x = 0; x < 5; x++)
  {
    analogWrite(led, arreglo[x]);
    delay(20);
  }
}
