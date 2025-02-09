void setup() {
  Serial.begin(9600);
}

void loop() {
  int bitArray[8];
  if (Serial.available()) {
    byte c = Serial.read();
    
    for (int i = 7; i >= 0; i--) { 
      bitArray[i] = (c % 2);
      c /= 2;
    }

    for (int i = 0; i < 8; i++) { 
      Serial.print(bitArray[i]);  
    }

  }
}
