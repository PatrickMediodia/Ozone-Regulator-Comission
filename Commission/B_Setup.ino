void setup() {
  pinMode(BTN_Start, INPUT);
  pinMode(BTN_Stop, INPUT);
  pinMode(OzoneEmitter, OUTPUT);
  pinMode(CarbonFilter, OUTPUT);

  Serial.begin(9600);
  while (!Serial);

  //Initialize Ozone Sensor I2C Interface
  while(!Ozone.begin(Ozone_IICAddress)) {
    Serial.println("I2c device number error !");
    delay(500);
  }
  Ozone.setModes(MEASURE_MODE_PASSIVE);
  
  //Initialize LCD I2C Interface
  lcd.init();
  lcd.backlight();

  //startup tasks
  xTaskCreate(T_CheckOzone, "Sensor", 128, NULL, 1, &H_CheckOzone);
  vTaskSuspend(H_CheckOzone);
  
  xTaskCreate(T_Runtime, "Timer", 140, NULL, 1, &H_Runtime);
  vTaskSuspend(H_Runtime);
  
  xTaskCreate(T_CheckRunningStatus, "Buttons", 96, NULL, 1, &H_CheckRunningStatus);

  //initiate emitter and fan filter as off
  digitalWrite(OzoneEmitter, HIGH);
  digitalWrite(CarbonFilter, HIGH);
  
  displayStartMessage();
}

void loop() {}