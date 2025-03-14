volatile unsigned int currentCapture = 0;
volatile unsigned int previousCapture = 0;
volatile unsigned int captureDiff = 0;

void setup() {
  Serial.begin(9600);

  pinMode(8, INPUT);

  TCCR1A = 0;               // Normal mode
  TCCR1B = (1 << ICES1) |   // Capture on rising edge
           (1 << CS11);     // Prescaler = 8,

  TIMSK1 = (1 << ICIE1);
}

ISR(TIMER1_CAPT_vect) {
  //On every capture event:
  currentCapture = ICR1;
  captureDiff = currentCapture - previousCapture;
  previousCapture = currentCapture;
}

void loop() {
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 500) {
    noInterrupts();
    unsigned int diff = captureDiff;
    interrupts();

    if (diff != 0) {
      float freq = 2000000.0 / diff; // if prescaler=8
      Serial.print("Freq: ");
      Serial.print(freq);
      Serial.println(" Hz");
    }
    lastPrint = millis();
  }
}
