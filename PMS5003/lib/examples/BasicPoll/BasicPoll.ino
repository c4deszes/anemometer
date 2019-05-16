#include <PMS5003.h>

#define PMS5003_SET_PIN 2
#define PMS5003_RESET_PIN 3
PMS5003_Data data;
PMS5003 pms(Serial1);

void setup() {
	pinMode(PMS5003_SET_PIN, OUTPUT);       //PMS5003 SET
	pinMode(PMS5003_RESET_PIN, OUTPUT);       //PMS5003 RESET
	
	digitalWrite(PMS5003_SET_PIN, HIGH);
	digitalWrite(PMS5003_RESET_PIN, HIGH);
	
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
		Serial.print("\r\n");
	}
}