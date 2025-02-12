const double baudRate = 1000/45.45;

void setup() {

  pinMode(9, OUTPUT);
  cli();

  TCCR1A = (1 << COM1A0);   // Toggle OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS10); // prescaler = 1


  float desiredFrequency = 2295.0; //IDLE AT MARK - typical for most RTTY frameworks
  float calculatedOCR = (16000000.0 / (2.0 * 1 * desiredFrequency)) - 1.0;
  OCR1A = (uint16_t)(calculatedOCR + 0.5); // rounding with no truncation
  OCR1A = 0;

  // Re-enable interrupts.
  sei();

  Serial.begin(9600);
}

void sendFrequency(float targetFrequency);

void loop() {

  if (Serial.available()) {
    String inputstring = Serial.readStringUntil('\n');
    int totalBits = inputstring.length() * 8;
    int bitArray[totalBits];

    int index = 0;
      for (int j = 0; j < inputstring.length(); j++) {
      byte c = inputstring[j];

      for (int i = 7; i >= 0; i--) { 
        bitArray[index + i] = c % 2;  
        c /= 2;
      }
      index += 8;
    }

    // Print stored binary word
    for (int i = 0; i < totalBits; i++) {
      Serial.print(bitArray[i]);
      if(bitArray[i]==0){
        sendFrequency(2125.0);
      }
      else{
        sendFrequency(2295.0);
      }
      delay(baudRate);
    }
    Serial.println();
    Serial.println("*****MESSAGE SENT*****");
    sendFrequency(0);
  }
}


void sendFrequency(float targetFrequency){
  targetFrequency = targetFrequency;
  float calculatedOCR = (16000000.0 / (2.0 * 1 * targetFrequency)) - 1.0;
  OCR1A = (uint16_t)(calculatedOCR + 0.5);
}