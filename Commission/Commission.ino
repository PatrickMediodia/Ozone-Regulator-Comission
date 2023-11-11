using namespace std; 

#include <SPI.h>
#include <Wire.h>
#include <Timer.h>
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal_I2C.h>
#include "DFRobot_OzoneSensor.h"

//Pin outs
#define BTN_Start 2
#define BTN_Stop 3
#define CarbonFilter 8
#define OzoneEmitter 9

//For testing only
#define OzoneSensor 13

//Ozone Sensor Values
#define COLLECT_NUMBER   20              // collect number, the collection range is 1-100
#define Ozone_IICAddress OZONE_ADDRESS_3

Timer timer;
DFRobot_OzoneSensor Ozone;
LiquidCrystal_I2C lcd(0x27,16,2);

int StartState = LOW;    // Variable to store the state of the first button
int StopState = LOW;    // Variable to store the state of the second button
unsigned long startTime;     // Variable to store the start time
float ozoneReading = 0.0;   // initial ozone reading
unsigned long duration = 2UL * 60UL * 1000UL; // 5 minutes in milliseconds

float maximumValue = 5.00;
float minimumValue = 2.00;
float cleanupValue = 1.00;

void T_Runtime(void *pvParameters);
void T_CheckRunningStatus(void *pvParameters);
void T_CheckOzone(void *pvParameters);

TaskHandle_t H_CheckRunningStatus, H_CheckOzone, H_Runtime;