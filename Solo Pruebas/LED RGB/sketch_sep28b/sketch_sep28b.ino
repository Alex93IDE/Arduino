int redpin = 11; // select the pin for the red LED
int bluepin = 10; // select the pin for the blue LED
int greenpin = 9; // select the pin for the green LED
int val = 255;
void setup () {
  pinMode (redpin, OUTPUT);
  pinMode (bluepin, OUTPUT);
  pinMode (greenpin, OUTPUT);
  Serial.begin (9600);
}
void loop () {
  //for (val = 255; val > 0; val--)
  //{
    analogWrite (11, val);
    analogWrite (10, 255 - val);
    analogWrite (9, 255 - val);
    delay(250);
    analogWrite (10, val);
    analogWrite (11, 255 - val);
    analogWrite (9, 255 - val);
    delay(250);
   analogWrite (9, val);
    analogWrite (11, 255 - val);
    analogWrite (10, 255 - val);
    delay(250);
    analogWrite (9, val);
    analogWrite (11, 255 - val);
    analogWrite (10, 128 - val);
    delay(250);
    analogWrite (9, val);
    analogWrite (11, 128 - val);
    analogWrite (10, 60 - val);
    delay(250);
    analogWrite (10, val);
    analogWrite (11, 255 - val);
    analogWrite (9, 128 - val);
    delay(250);
    analogWrite (11, val);
    analogWrite (10, 60 - val);
    analogWrite (9, 128 - val);
    delay(250);
    analogWrite (11, val);
    analogWrite (9, 255 - val);
    analogWrite (10, 128 - val);
    delay(250);
}
