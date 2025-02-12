#define BIT0 0x00000001
const double baudRate = 1000/45.45;

void setup() {

  pinMode(9, OUTPUT);
  cli();

  TCCR1A = (1 << COM1A0);   // Toggle OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS10); // prescaler = 1


  float desiredFrequency = 2295.0; //IDLE AT MARK - typical for most RTTY frameworks
  float calculatedOCR = (16000000.0 / (2.0 * 1 * desiredFrequency)) - 1.0;
  OCR1A = (uint16_t)(calculatedOCR + 0.5); // rounding with no truncation

  // Re-enable interrupts.
  sei();

  Serial.begin(9600);
}

void sendFrequency(float targetFrequency);

void loop() {
  if (Serial.available()) {
    String inputstring = Serial.readStringUntil('\n');

      for (int j = 0; j < inputstring.length(); j++) {
      byte c = inputstring[j]; // do I need to read this backwards?
      sendFrequency(2125.0); //START BIT
      delay(baudRate); 
      for (int i = 0; i < 8; i++) { 
        int bit = (c >> i) & BIT0;
        if(bit==0){
          sendFrequency(2125.0);
        }
        else{
          sendFrequency(2295.0);
        }
        delay(baudRate);
        Serial.print(bit); //debug
      }
      sendFrequency(2295.0); // STOP BIT
      delay(baudRate);
    }
  }
}

void sendFrequency(float targetFrequency){
  float calculatedOCR = (16000000.0 / (2.0 * 1 * targetFrequency)) - 1.0;
  OCR1A = (uint16_t)(calculatedOCR + 0.5);
}