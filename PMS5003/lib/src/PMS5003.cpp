#include "Arduino.h"
#include "PMS5003.h"

/*
Creates a new sensor object that reads data from the given stream.
Exampe:
	PMS5003 sensor(Serial1);
*/
PMS5003::PMS5003(Stream& stream): _stream(stream), b_state(PMS5003_BH) {}

/*
Just to keep the semantics of the Arduino ecosystem
*/
void PMS5003::begin() {
	
}

/*
Puts the sensor into low current mode
*/
void PMS5003::sleep() {
	//TODO: send command
}

/*
Wakes the sensor from sleep mode
*/
void PMS5003::wake() {
	//TODO: send command
}

/*
Turns on the fan of the sensor
*/
void PMS5003::active() {
	//TODO: send command
}

/*
Turns off the fan of the sensor
*/
void PMS5003::passive() {
	//TODO: send command
}

/*
Returns true if there's unread data from the sensor
Returns false otherwise
*/
bool PMS5003::available() {
	return hasData;
}

/*
Returns true if data has been successfully read
Returns false otherwise
*/
bool PMS5003::read(PMS5003_Data& dst) {
	if(!hasData) {
		return false;
	}
	dst = _buffer;
	hasData = false;
	return true;
}

/*
Polls the stream for incoming bytes then updates the state and incoming data
based on that.

Check the BasicPoll example
*/
void PMS5003::poll() {
	if(!_stream.available()) {
		return;
	}
	uint8_t in_data = _stream.read();
	if(b_state == PMS5003_BH) {
		b_data |= ((uint16_t)in_data) << 8;
		b_state = PMS5003_BL;
	}
	else {
		b_data |= in_data;
		b_state = PMS5003_BH;
		
		if(!packet_started && b_data == 0x424D) {
			packet_started = true;
		}
		else if(packet_started && packet_length == 0) {
			packet_length = b_data;
		}
		else if(packet_started && packet_length != 0) {
			uint8_t* buffer = (uint8_t*)(&_buffer);
			buffer[data_offset] = b_data;
			data_offset += 2;
			packet_length-=2;
			if(packet_length == 0) {
				hasData = true;
				packet_started = false;
				data_offset = 0;
			}
		}
		b_data = 0;
	}
}