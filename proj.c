#include<stdio.h>
#define ON 1
#define OFF 0
#define WITH_ENGINE_TEMP_CONTROLLER 1
#if WITH_ENGINE_TEMP_CONTROLLER
#define ENGINE_TEMP_CONTROLLER 1
#endif
/*************************************************************** Vehicle Variables **********************************************************/
unsigned char EngineState = OFF;
unsigned int VehicleSpeed = 0;
unsigned char AC = OFF;
float RoomTemp = 35;
unsigned char EngineTempController = OFF;
float EngineTemp = 90;
/*************************************************************** Functions Prototypes***********************************************************/
void ReadEngineState(char *in);
void ReadSensorState(char *sens);
void SetTrafficLight(void);
void SetRoomTemp(void);
void SetEngineTemp(void);
void Speed30(void);
void printEngineState(void);
void printACState(void);
void printVehicleSpeed(void);
void printRoomTemp(void);
void printEngineControllerState(void);
void printEngineTemp(void);
void Display(void);
void Read(void);

int main(void) {
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	/*************************************************************** Program starts *********************************************************/
	char Engine_input;
	ReadEngineState(&Engine_input);
	if (Engine_input == 'c')
		return 0;
	if (Engine_input == 'a') {
		Read();
		return 0;
	}
}
/******************************************************** Functions Definitions************************************************************/
void ReadEngineState(char *in) {
	char input;
	do {
		printf("\nChoose Action to do with the Engine\n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n");
		scanf(" %c", &input);
		if (input == 'a') {
			EngineState = ON;
			printf("Vehicle Engine is ON\n");
		}
		if (input == 'b') {
			EngineState = OFF;
			printf("Vehicle Engine is OFF\n");
		}
		if (input == 'c') {
			printf("System is Quitted\n");
		}
	} while (input == 'b');
	*in = input;
}
void ReadSensorState(char *sens) {
	char sensor;
	printf("\nChoose Action to do with the Sensors\n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#ifdef ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif
	scanf(" %c", &sensor);
	*sens = sensor;
}
void SetTrafficLight(void) {
	char color;
	printf("Choose the Traffic Color G or O or R\n");
	scanf(" %c", &color);
	if ((color == 'G') || (color == 'g')) {
		VehicleSpeed = 100;
	}
	if ((color == 'O') || (color == 'o')) {
		VehicleSpeed = 30;
	}
	if ((color == 'R') || (color == 'r')) {
		VehicleSpeed = 0;
	}
}
void SetRoomTemp(void) {
	printf("Enter Room Temperature\n");
	scanf(" %f", &RoomTemp);
	if (RoomTemp < 10) {
		AC = ON;
		RoomTemp = 20;
	} else if (RoomTemp > 30) {
		AC = ON;
		RoomTemp = 20;
	} else {
		AC = OFF;
	}
}
void SetEngineTemp(void) {
	printf("Enter Engine Temperature\n");
	scanf(" %f", &EngineTemp);
	if (EngineTemp < 100) {
		EngineTempController = ON;
		EngineTemp = 125;
	} else if (EngineTemp > 150) {
		EngineTempController = ON;
		EngineTemp = 125;
	} else {
		EngineTempController = OFF;
	}
}
void Speed30(void) {
	if (AC == OFF) {
		AC = ON;
		RoomTemp = (RoomTemp * (5.0 / 4)) + 1;
	}
#ifdef ENGINE_TEMP_CONTROLLER
	if (EngineTempController == OFF) {
		EngineTempController = ON;
		EngineTemp = (EngineTemp * (5.0 / 4)) + 1;
	}
#endif
}
void printEngineState(void) {
	EngineState == ON ? printf("Engine is ON\n") : printf("Engine is OFF\n");
}
void printACState(void) {
	AC == ON ? printf("AC is ON\n") : printf("AC is OFF\n");
}
void printVehicleSpeed(void) {
	printf("Vehicle Speed = %d Km/Hr\n", VehicleSpeed);
}
void printRoomTemp(void) {
	printf("Room Temperature = %f C\n", RoomTemp);
}
void printEngineControllerState(void) {
	EngineTempController == ON ?
			printf("Engine Temperature Controller is ON\n") :
			printf("Engine Temperature Controller is OFF\n");
}
void printEngineTemp(void) {
	printf("Engine Temperature = %f C\n", EngineTemp);
}
void Display(void) {
	printEngineState();
	printACState();
	printVehicleSpeed();
	printRoomTemp();
#ifdef ENGINE_TEMP_CONTROLLER
	printEngineControllerState();
	printEngineTemp();
#endif
}
void Read(void) {
	int printnow = 0;
	char sensor = 0;
	while (1) {
		ReadSensorState(&sensor);
		if (sensor == 'a') {
			char input1;
			ReadEngineState(&input1);
			if (input1 == 'c')
				return;
		}
		if (sensor == 'b') {
			SetTrafficLight();
			printnow = 1;
		}
		if (sensor == 'c') {
			SetRoomTemp();
			printnow = 1;
		}
		if (sensor == 'd') {
#ifdef ENGINE_TEMP_CONTROLLER
			SetEngineTemp();
			printnow = 1;
#endif
		}
		if (VehicleSpeed == 30) {
			Speed30();
		}
		/****************************************************** Display Data ********************************************************************/
		if (printnow) {
			Display();
			printnow = 0;
		}
	}
	return;
}
