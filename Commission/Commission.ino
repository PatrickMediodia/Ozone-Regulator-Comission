#include <SPI.h>
#include <Wire.h>
#include <Timer.h>
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal_I2C.h>
#include "DFRobot_OzoneSensor.h"

//Pin outs
#define BTN_Start 2
#define BTN_Stop 3
#define CarbonFilter 10
#define OzoneEmitter 11

//Ozone Sensor Values
#define COLLECT_NUMBER   20              // collect number, the collection range is 1-100
#define Ozone_IICAddress OZONE_ADDRESS_3

Timer timer;
DFRobot_OzoneSensor Ozone;
LiquidCrystal_I2C lcd(0x27,16,2);

int StartState = LOW;    // Variable to store the state of the first button
int StopState = LOW;    // Variable to store the state of the second button
int16_t ozoneReading = 0.0;   // initial ozone reading

uint32_t duration = 5UL * 60UL * 1000UL; // 5 minutes in milliseconds
//uint32_t duration = 0.25 * 60 * 1000; // Use if under 1 minute

bool stopAndRegulateOzone = false;
bool maxSafeOzoneReached = false;

int16_t maximumValue = 6.00;
int16_t minimumValue = 4.00;
int16_t safeValue = 2.00;

void T_Runtime(void *pvParameters);
void T_CheckRunningStatus(void *pvParameters);
void T_CheckOzone(void *pvParameters);

TaskHandle_t H_CheckRunningStatus, H_CheckOzone, H_Runtime;