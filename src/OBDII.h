#ifndef __OBDII_H
#define __OBDII_H

#define VARIABLE_RESPONSE_LENGTH 0

typedef struct OBDIIResponse {
	int success;

	union {
		float floatValue;
		unsigned int bitfieldValue;
		char *stringValue; // for VIN or ECU name
		struct {
			char (*troubleCodes)[6];
			int numTroubleCodes;
		} DTCs;
	};
} OBDIIResponse;

struct OBDIICommand;
typedef void (*OBDIIResponseDecoder)(OBDIIResponse *, unsigned char *, int);

typedef struct OBDIICommand {
	char *name;
	unsigned char payload[2];
	short expectedResponseLength;
	OBDIIResponseDecoder responseDecoder;
} OBDIICommand;

struct OBDIICommands {
	OBDIICommand supportedPIDs_0_to_20;
	OBDIICommand monitorStatus;
	OBDIICommand freezeDTC;
	OBDIICommand fuelSystemStatus;
	OBDIICommand calculatedEngineLoad;		// Percentage
	OBDIICommand engineCoolantTemperature;		// Celsius
	OBDIICommand bank1ShortTermFuelTrim;		// Percentage
	OBDIICommand bank1LongTermFueldTrim;		// Percentage
	OBDIICommand bank2ShortTermFuelTrim; 		// Percentage
	OBDIICommand bank2LongTermFuelTrim; 		// Percentage
	OBDIICommand fuelPressure; 			// kPA
	OBDIICommand intakeManifoldAbsolutePressure; 	// kPA
	OBDIICommand engineRPMs;			// rpm
	OBDIICommand vehicleSpeed;			// km/h
	OBDIICommand timingAdvance;			// Degrees before TDC
	OBDIICommand intakeAirTemperature;		// Celsius
	OBDIICommand DTCs;
	OBDIICommand VIN;
	OBDIICommand ECUName;
};

extern struct OBDIICommands OBDIICommands;

OBDIIResponse OBDIIDecodeResponseForCommand(OBDIICommand *command, unsigned char *responsePayload, int len);
void OBDIIResponseFree(OBDIIResponse *response);

#endif /* OBDII.h */
