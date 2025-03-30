#define BIT0 0x00000001
const double delayTime = (1.0 / 45.45) * 1000;  // Convert to milliseconds
const double MARK = 2295.0;
const double SPACE = 2125.0;

void setup() {
  pinMode(9, OUTPUT);
  cli();

  TCCR1A = (1 << COM1A0);   // Toggle OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS10); // prescaler = 1

  float desiredFrequency = MARK; //IDLE AT MARK - typical for most RTTY frameworks
  float calculatedOCR = (16000000.0 / (2.0 * 1 * desiredFrequency)) - 1.0;
  OCR1A = (uint16_t)(calculatedOCR + 0.5); // rounding with no truncation

  sei();
  Serial.begin(9600);
}

void sendFrequency(float targetFrequency);
void sendChar(byte c);

void loop() {
  if (Serial.available()) {
    String inputstring = Serial.readStringUntil('\n');
      for (int j = 0; j < inputstring.length(); j++) {
      byte c = inputstring[j]; 
      sendChar(c); 
    }
    Serial.println("MESSAGE SENT");
  }
}

void sendChar(byte c){
  sendFrequency(SPACE); //START BIT
  delay(delayTime);
  for (int i = 0; i < 8; i++) { //send characters from LSB to MSB
    int bit = (c >> i) & BIT0;
    if(bit==0){
      sendFrequency(SPACE);
    }
    else{
      sendFrequency(MARK);
    }
    delay(delayTime);
    Serial.print(bit);
    }
    sendFrequency(MARK); // STOP BIT/IDLE
    delay(delayTime*5);
    Serial.println();
    Serial.print("***** CHARACTER '");
    Serial.print((char) c); //Serial confirmation for debugging - will remove all serial prints for actual deployment
    Serial.println("' SENT *****");
    //sendFrequency(2400.0);
}

void sendFrequency(float targetFrequency){
  float calculatedOCR = (16000000.0 / (2.0 * 1 * targetFrequency)) - 1.0;
  OCR1A = (uint16_t)(calculatedOCR + 0.5);
}
