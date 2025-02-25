/* FreqMeasure - Example with serial output
 * http://www.pjrc.com/teensy/td_libs_FreqMeasure.html
 *
 * This example code is in the public domain.
 */
#include <FreqMeasure.h>
void readFrequency();
void setup() {
  Serial.begin(9600);
  FreqMeasure.begin();
}

double sum=0;
int count=0;


float loop() {
  readFrequency
  
}


float readFrequency(){
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      Serial.println(frequency);
      sum = 0;
      count = 0;
      return frequency;
    }
  }
}