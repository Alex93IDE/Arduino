
#include <FreqMeasure.h>

void setup() {
  Serial.begin(2000000);
  FreqMeasure.begin();
}

double sum=0;
int count=0;

void loop() {
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      Serial.print(frequency);
      Serial.println(" Hz");
      sum = 0;
      count = 0;
    }
  }
}

