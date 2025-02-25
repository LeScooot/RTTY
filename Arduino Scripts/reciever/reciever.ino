double currentVal = 0;
double previousVal = 0;
double difference = 0;
double period;
const int input = A1;
double time1, time2, frequency;

void setup() {
  pinMode(A1, INPUT);

}

void loop() {
  previousVal = currentVal;
  currentVal = analogRead(input);
  while (previousVal > currentVal){
  previousVal = currentVal;
  currentVal = analogRead(input);
  }
  time1 = millis();

  while (previousVal < currentVal){
  previousVal = currentVal;
  currentVal = analogRead(input);
  }
  time2 = millis();
  period = time2-time1;
  frequency = 1/period;
  Serial.print("Period");
}
