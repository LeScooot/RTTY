const int input = 9;
int time = 0;
int previoustime;
double period;
double frequency;
void CalculateFrequency();

void setup() {
  pinMode(input, INPUT);
  attachInterrupt(digitalPinToInterrupt(input), RISING, CalculateFrequency);
  Serial.begin(9600);

}

void loop() {
  period = time - previoustime;
  if(period != 0){
    frequency = 1/period;
  }
  else{
    frequency = 0;
  }
  Serial.print("Frequency: ");
  Serial.println(frequency);
  Serial.print("Period: ");
  Serial.println(period);
}


void CalculateFrequency(){
  previoustime = time;
  time = millis();
}