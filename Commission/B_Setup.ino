void setup() {
  pinMode(BTN_Start, INPUT);
  pinMode(BTN_Stop, INPUT);
  pinMode(Fan_Relay, OUTPUT);
  pinMode(OzoneSensor, INPUT);
  
  Serial.begin(9600);
  while (!Serial);

  lcd.init();
  lcd.backlight();

  xTaskCreate(T_CheckRunningStatus, "Buttons", 128, NULL, 1, &H_CheckRunningStatus);

  xTaskCreate(T_CheckOzone, "Sensor", 128, NULL, 1, &H_CheckOzone);
  vTaskSuspend(H_CheckOzone);

  xTaskCreate(T_Runtime, "Timer", 128, NULL, 1, &H_Runtime);
  vTaskSuspend(H_Runtime);

  displayStartMessage();
}

void loop() {}