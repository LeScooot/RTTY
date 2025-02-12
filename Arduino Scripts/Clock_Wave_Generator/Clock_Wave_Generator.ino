void setup() {
  pinMode(9, OUTPUT);

  TCCR1A = (1 << COM1A0);   // Toggle OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS10); // prescaler = 1


  float desiredFrequency = 2125.0;
  float calculatedOCR = (16000000.0 / (2.0 * 1 * desiredFrequency)) - 1.0;
  OCR1A = (uint16_t)(calculatedOCR + 0.5); // rounding with no truncation

  // Re-enable interrupts.
}

void loop() {
//nothing in loop, pin9 trigger is automatically toggled with the code in the setup loop
}
