void StopSystem() {
  //if paused is used, and start is ran, it will restart the value of the timer
  timer.pause();

  //Stop the timer and the ozone sensor
  vTaskSuspend(H_Runtime);

  //turn off emitter
  digitalWrite(OzoneEmitter, HIGH);

  //turn on filter until ozone is high
  while(OzoneState == HIGH) {
    digitalWrite(CarbonFilter, LOW);   
  }

  vTaskSuspend(H_CheckOzone);
  digitalWrite(CarbonFilter, HIGH);

  displayStartMessage();
}

void displayStartMessage() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Ozone Regulator");

  lcd.setCursor(3, 1);
  lcd.print("Press Start");
}

void displayOzoneReading() {
  //display ozone value
  lcd.setCursor(2, 0);
  lcd.print("0zone: 5 ppm");
}

void displayTimeElapsed() {
  float timeElapsed = (timer.read() / 1000.0) / 60.0;
  int timeElapsedWhole = static_cast<int>(timeElapsed);

  char secondsCount[2];
  float seconds = (timeElapsed - timeElapsedWhole) * 60;
  dtostrf(seconds, 2, 0, secondsCount);
  if (seconds <= 9.9999) {
    secondsCount[0] = '0';  
  }

  //display time elapsed
  lcd.setCursor(3, 1);
  lcd.print("Time: ");

  //display minutes
  lcd.setCursor(9, 1);
  lcd.print(timeElapsedWhole);

  lcd.setCursor(10, 1);
  lcd.print(":");

  //display seconds
  lcd.setCursor(11, 1);
  lcd.print(secondsCount);
}