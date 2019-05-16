#include <PMS5003.h>

#define GP2Y1010_LED 11

PMS5003_Data data;
PMS5003 pms(Serial1);

uint16_t GP2Y1010_read = 0;

void setup() {
  analogReadResolution(12);
  analogWriteResolution(12);
  
  pinMode(2, OUTPUT);       //PMS5003 SET
  pinMode(4, OUTPUT);       //PMS5003 RESET

  pinMode(GP2Y1010_LED, OUTPUT);      //GP2Y1010 LED
  digitalWrite(GP2Y1010_LED, HIGH);
  pinMode(A0, INPUT);       //GP2Y1010 Receiver

  pinMode(3, OUTPUT);       //NTC100 driving
  pinMode(A5, INPUT);       //NTC100 read
  analogWrite(3, 2048);

  pinMode(A1, INPUT);       //digital anemometer High impedance
  pinMode(A2, INPUT);       //digital ... low
  
  pinMode(A3, INPUT);       //Analog anemometer
  
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  Serial.begin(9600);
  Serial1.begin(9600);
  pms.begin();
}

void loop() {
  pms.poll();
  if(pms.available() && pms.read(data)) {
    Serial.print(data.PM_AE_UG_1_0);
    Serial.print('\t');
    Serial.print(data.PM_AE_UG_2_5);
    Serial.print('\t');
    Serial.print(data.PM_AE_UG_10_0);
    Serial.print('\t');
    
    Serial.print(data.PM_CT_0_3);
    Serial.print('\t');
    Serial.print(data.PM_CT_0_5);
    Serial.print('\t');
    Serial.print(data.PM_CT_1_0);
    Serial.print('\t');
    Serial.print(data.PM_CT_2_5);
    Serial.print('\t');
    Serial.print(data.PM_CT_5_0);
    Serial.print('\t');
    Serial.print(data.PM_CT_10_0);
    Serial.print('\t');
    
    Serial.print(GP2Y1010_read);
    Serial.print('\t');
    
    Serial.print(analogRead(A1));
    Serial.print('\t');
    Serial.print(analogRead(A2));
    Serial.print('\t');
    
    Serial.print(analogRead(A3));
    Serial.println();
  }

  digitalWrite(GP2Y1010_LED, LOW);
  delayMicroseconds(280);
  GP2Y1010_read = analogRead(A0);
  delayMicroseconds(40);
  digitalWrite(GP2Y1010_LED, HIGH);
  delay(10);
}
