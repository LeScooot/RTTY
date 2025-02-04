const int IR = 9;
const int high_freq = 2125;
const int low_freq = 2295;
const int

void setup() {
  pinmode(IR, OUTPUT);
  Serial.begin(9600);
}

void square_wave(int pin, int frequency);

void loop() {
  square_wave(IR, high_freq);

}

void square_wave(int pin, int frequency){
  int currTime = millis();
  int stoptime = currTime + 
  double period = 1/frequency
  digitalWrite(pin, HIGH);
  delay(period/2);
  deigitalWrite(pin, LOW);
  delay(period/2);
}
void testing_function(){
  square_wave(IR, high_freq);
  delay(50)
}
void string_to_binary(int& string, int& binary){
  char character;
  byte b;
  array
  for(int i = 0; i < string.length(); i++){
    character = string.charAt(i);
    for(int i = 0; i < 7; i++){
      c = bitread(character, i);

      
    }
    
  }

}