/*
  Precise Frequency Generation Using Timer1 in CTC Mode

  This example configures Timer1 to toggle OC1A (Arduino digital pin 9)
  at a frequency determined by the OCR1A value.
  
  Frequency formula:
    f = F_CPU / (2 * Prescaler * (OCR1A + 1))
    
  For a 16 MHz clock and a prescaler of 8, for example:
    OCR1A = (16,000,000 / (2 * 8 * f)) - 1
*/

void setup() {
  // Set OC1A (pin 9) as output.
  pinMode(9, OUTPUT);

  // Disable interrupts while setting up Timer1.
  cli();

  // Configure Timer1:
  // - CTC mode: WGM12 bit in TCCR1B must be set.
  // - Toggle OC1A on Compare Match: COM1A0 in TCCR1A set to 1.
  // - Prescaler set to 8: CS11 bit in TCCR1B set to 1.
  TCCR1A = (1 << COM1A0);                     // Toggle OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS10);          // CTC mode, prescaler = 8

  // Set compare value for desired frequency.
  // For 2125 Hz:
  float desiredFrequency = 2125.0;
  float calculatedOCR = (16000000.0 / (2.0 * 1 * desiredFrequency)) - 1.0;
  OCR1A = (uint16_t)(calculatedOCR + 0.5);

  // Re-enable interrupts.
  sei();
}

void loop() {
  // Nothing required in loop() since Timer1 handles the output autonomously.
  // To switch frequencies on the fly, you can update OCR1A here based on conditions.
  // For example:
  //
  // if (someCondition) {
  //   OCR1A = 470; // For 2125 Hz
  // } else {
  //   OCR1A = 434; // For 2295 Hz (or 435, based on calibration)
  // }
}
