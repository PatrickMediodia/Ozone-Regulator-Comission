void setup() {
  pinMode(BTN_Start, INPUT);
  pinMode(BTN_Stop, INPUT);
  pinMode(OzoneEmitter, OUTPUT);
  pinMode(CarbonFilter, OUTPUT);
  pinMode(OzoneSensor, INPUT);
  
  Serial.begin(9600);
  while (!Serial);

  lcd.init();
  lcd.backlight();

  xTaskCreate(T_CheckOzone, "Sensor", 128, NULL, 1, &H_CheckOzone);
  vTaskSuspend(H_CheckOzone);

  xTaskCreate(T_Runtime, "Timer", 128, NULL, 1, &H_Runtime);
  vTaskSuspend(H_Runtime);

  xTaskCreate(T_CheckRunningStatus, "Buttons", 128, NULL, 1, &H_CheckRunningStatus);
  
  //initiate emitter and fan filter as off
  digitalWrite(OzoneEmitter, HIGH);
  digitalWrite(CarbonFilter, HIGH);

  displayStartMessage();
}

void loop() {}