const int IR = 9;
// const unsigned int low_freq = 2125;
const unsigned int low_freq = 2125;
const unsigned int high_freq = 2295;
const double timing = 1/(45.45);

int counter = 0;
double delayTime;

void setup() {
  pinMode(IR, OUTPUT);
  Serial.begin(9600);
}

// void square_wave(int pin, int frequency);
void square_wave_tone(int frequency);
void new_wave(int frequency);

void loop() {
  new_wave(low_freq);
  // if(counter%2 == 0){
  //   square_wave_tone(high_freq);
  // }
  // else{
  //   square_wave_tone(low_freq);
  // }
  // square_wave_tone(low_freq);
}
void square_wave_tone(int frequency){
  tone(IR, frequency);
  // delay(timing * 1000);
}
void new_wave(int frequency){
  delayTime = (1.0/frequency)/2.0;
  digitalWrite(IR, HIGH);
  delayMicroseconds(delayTime * 1000000); // half the period
  digitalWrite(IR, LOW);
  delayMicroseconds(delayTime * 1000000);
}
// void square_wave(int pin, int frequency){
//   int currTime = millis();
//   int stoptime = currTime + 
//   double period = 1/frequency
//   digitalWrite(pin, HIGH);
//   delay(period/2);
//   deigitalWrite(pin, LOW);
//   delay(period/2);
// }



