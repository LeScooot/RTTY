const int IR = 9;
const unsigned int high_freq = 2125;
const unsigned int low_freq = 2295;
const double timing 1/(45.45);

int counter = 0;

void setup() {
  pinmode(IR, OUTPUT);
  Serial.begin(9600);
}

void square_wave(int pin, int frequency);

void loop() {
  if(counter%2 == 0){
    square_wave_tone(high_freq);
  }
  else{
    square_wave_tone(low_freq);
  }
  delay(timing * 1000);
  counter++
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

void square_wave_tone(int frequency){
  tone(IR, frequency);
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