void setup() {
  pinMode(BTN_Start, INPUT);
  pinMode(BTN_Stop, INPUT);
  pinMode(Fan_Relay, OUTPUT);
  pinMode(OzoneSensor, INPUT);
  
  Serial.begin(9600);
  while (!Serial);

  //initialize lcd
  //lcd.init();
  //lcd.backlight();

  xTaskCreate(T_CheckRunningStatus, "Buttons", 256, NULL, 1, &H_CheckRunningStatus);

  xTaskCreate(T_CheckOzone, "Sensor", 256, NULL, 1, &H_CheckOzone);
  vTaskSuspend(H_CheckOzone);

  xTaskCreate(T_Runtime, "Timer", 256, NULL, 1, &H_Runtime);
  vTaskSuspend(H_Runtime);
}

void loop() {}