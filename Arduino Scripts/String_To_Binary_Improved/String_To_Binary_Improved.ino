void setup() {
  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {
    String inputstring = Serial.readStringUntil('\n');
    int totalBits = inputstring.length() * 8;
    int bitArray[totalBits];
    byte c = Serial.read();

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
    }
  }
}
