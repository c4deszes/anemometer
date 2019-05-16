#ifndef PMS5003_H
#define PMS5003_H

#include "Stream.h"

#define PMS5003_BH 1
#define PMS5003_BL 0

struct PMS5003_Data {
	// Standard Particles, CF=1
	uint16_t PM_SP_UG_1_0;
	uint16_t PM_SP_UG_2_5;
	uint16_t PM_SP_UG_10_0;

	// Atmospheric environment
	uint16_t PM_AE_UG_1_0;
	uint16_t PM_AE_UG_2_5;
	uint16_t PM_AE_UG_10_0;
	
	//Particle count
	uint16_t PM_CT_0_3;
	uint16_t PM_CT_0_5;
	uint16_t PM_CT_1_0;
	uint16_t PM_CT_2_5;
	uint16_t PM_CT_5_0;
	uint16_t PM_CT_10_0;
	
	uint16_t reserved;
	uint16_t checksum;
};

struct PMS5003 {
	PMS5003(Stream&);
	void begin();
	
	void sleep();
	void wake();
	void active();
	void passive();
	
	bool available();
	bool read(PMS5003_Data&);
	void poll();
	
private:
	Stream& _stream;
	PMS5003_Data _buffer;
	
	uint8_t b_state;
	uint16_t b_data;
	bool hasData;
	
	bool packet_started;
	uint16_t packet_length;
	uint16_t data_offset;
};

#endif