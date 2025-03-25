unsigned int currentCapture = 0;
unsigned int previousCapture = 0;
unsigned int captureDiff = 0;
#define BIT0 0x00000001
const double delayTime = (1.0 / 45.45) * 1000000;  // Convert to microseconds
const double MARK = 2295.0;
const double SPACE = 2125.0;
char c[8];
int frequencyToBinary(int frequency);
unsigned int diff;
int frequency;

void setup() {
  Serial.begin(9600);

  pinMode(8, INPUT);

  TCCR1A = 0;               
  TCCR1B = (1 << ICES1) |   // Capture on rising edge
           (1 << CS11);     // Prescaler = 8

  TIMSK1 = (1 << ICIE1);
}

ISR(TIMER1_CAPT_vect) {
  //On every capture event
  currentCapture = ICR1;
  captureDiff = currentCapture - previousCapture;
  previousCapture = currentCapture;
}

void loop() {
  noInterrupts();
  diff = captureDiff;
  interrupts();
  frequency = 2000000.0 / diff;
  Serial.println(frequency);
  if(frequencyToBinary(frequency) == 0){
    delayMicroseconds(delayTime);
      for(int i = 0; i < 8; i++){
        noInterrupts();
        diff = captureDiff;
        interrupts();
        frequency = 2000000.0 / diff;
        c[i] = frequencyToBinary(frequency);
        delayMicroseconds(delayTime);
      }
  }
  for(int i = 0; i < 8; i++){
    Serial.print(c[i]);
  }
  }

int frequencyToBinary(int frequency){
  if(frequency > 2208){
    return 1;
  }
  else{
    return 0;
  }
}
