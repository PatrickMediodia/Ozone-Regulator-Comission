using namespace std; 

#include <SPI.h>
#include <Wire.h>
#include <Timer.h>
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal_I2C.h>

#define BTN_Start 2
#define BTN_Stop 3
#define CarbonFilter 8
#define OzoneEmitter 9
#define OzoneSensor 13

Timer timer;
LiquidCrystal_I2C lcd(0x27,16,2);

int OzoneState;
int StartState = LOW;    // Variable to store the state of the first button
int StopState = LOW;    // Variable to store the state of the second button
unsigned long startTime;     // Variable to store the start time
unsigned long duration = 0.25 * 60 * 1000; // 5 minutes in milliseconds
bool functionExecuted = false;

void T_Runtime(void *pvParameters);
void T_CheckRunningStatus(void *pvParameters);
void T_CheckOzone(void *pvParameters);

TaskHandle_t H_CheckRunningStatus, H_CheckOzone, H_Runtime;