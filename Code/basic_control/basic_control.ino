void setup() {
  analogReadResolution(12);
  analogWriteResolution(12);
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

int onTime = 5000;
int period = 10000;

void loop() {
  digitalWrite(9, HIGH);
  delayMicroseconds(300);
  
  int ref = analogRead(A1);
  int heated = analogRead(A0);

  if(heated > ref) {
    if(onTime < period) {
      onTime += 10;
    }
  }
  else {
    if(onTime > 5000) {
      onTime -= 10;
    }
  }

  delayMicroseconds(onTime);
  digitalWrite(9, LOW);
  delayMicroseconds(period - onTime);
}

int targetOffset(int temperature) {
  return 70;
}
