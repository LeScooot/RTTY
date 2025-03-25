 
unsigned int currentCapture = 0;
unsigned int previousCapture = 0;
unsigned int captureDiff = 0;
const double BAUD_RATE = 45.45;  
const double BIT_TIME_US = (1.0 / BAUD_RATE) * 1000000;  
// const double BIT_TIME_US = 22002.20022;
const double HALF_BIT_TIME_US = BIT_TIME_US / 2;
const double MARK_FREQ = 2295.0;  
const double SPACE_FREQ = 2125.0; 
const int FREQ_THRESHOLD = 2208;  
#define BIT0 0x00000001

int frequencies[8];


enum UartState {
  IDLE,           
  RECEIVING_DATA, 
  STOP_BIT        
};


UartState state = IDLE;
byte receivedByte = 0;
int bitIndex = 0;
unsigned long nextSampleTime = 0;
bool newByteReceived = false;

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);

  TCCR1A = 0;              
  TCCR1B = (1 << ICES1) |  
           (1 << CS11);   

  TIMSK1 = (1 << ICIE1); 
  Serial.println();
}


ISR(TIMER1_CAPT_vect) {
  currentCapture = ICR1;
  captureDiff = currentCapture - previousCapture;
  previousCapture = currentCapture;
}

int frequencyToBinary(int frequency) {
  if(frequency > FREQ_THRESHOLD){
    return 1;
  }
  else{
    return 0;
  }
}

int getCurrentFrequency() {
  noInterrupts();
  unsigned int diff = captureDiff;
  interrupts();

  return (2000000.0 / diff);
  
  // return (diff > 0) ? 2000000.0 / diff : 0;
}

void loop() {
  int frequency = getCurrentFrequency();
  int bit = frequencyToBinary(frequency);
  unsigned long currentTime = micros();
  // Serial.println(frequency);
  
  switch (state) {
    case IDLE:
      if (bit == 0) {
        state = RECEIVING_DATA;
        bitIndex = 0;
        receivedByte = 0;
        nextSampleTime = currentTime + HALF_BIT_TIME_US + BIT_TIME_US;
        // nextSampleTime = currentTime + BIT_TIME_US;
        // Serial.println("STOP");
      
      }

      break;
      
    case RECEIVING_DATA:
      if (currentTime >= nextSampleTime) {
        frequency = getCurrentFrequency();
        bit = frequencyToBinary(frequency);
        
        if (bit == 1) {
          receivedByte |= (1 << bitIndex);
        }

        frequencies[bitIndex] = frequency;
        
        bitIndex++;
        nextSampleTime += BIT_TIME_US;
        
        if (bitIndex >= 8) {
          state = STOP_BIT;
          // Serial.println("STOP");
        }
      }
      // Serial.println("COLELCT");
      break;
      
    case STOP_BIT:
      if (currentTime >= nextSampleTime) {
        frequency = getCurrentFrequency();
        bit = frequencyToBinary(frequency);

        if((char)receivedByte == '#'){
          Serial.println();
        }
        
        if (bit == 1) {
        if((char)receivedByte != '#')
          Serial.print((char)receivedByte);

        // for(int i = 0; i < 8; i++){
        //   Serial.println((receivedByte >> i) & BIT0);
        // }
        
        state = IDLE;
        // Serial.println("IDLE");
      }
      //Serial.println("STOP");
      break;
  }
  }
}