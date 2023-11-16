void StopSystem() {
  //turn off emitter
  vTaskSuspend(H_CheckOzone);
  digitalWrite(OzoneEmitter, HIGH);

  ozoneReading = Ozone.readOzoneData(COLLECT_NUMBER) / 1000.0;
  
  //turn on filter while ozone is high
  if (ozoneReading > safeValue) {
    displayCleaningMessage();
    //Serial.println("Regulating Ozone");
    digitalWrite(CarbonFilter, LOW);

  } else {
    //if paused is used, and start is ran, it will restart the value of the timer
    timer.pause();
    digitalWrite(CarbonFilter, HIGH);
    
    //Stop the timer task which is running this stop system function
    displayStartMessage();
    //Serial.println("Ozone Regulated");

    stopAndRegulateOzone = false;
    vTaskSuspend(H_Runtime);
  }
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
  lcd.setCursor(1, 0);
  lcd.print("0zone: ");

  lcd.setCursor(8, 0);
  lcd.print(ozoneReading);

  lcd.setCursor(12, 0);
  lcd.print(" ppm");
}

void displayCleaningMessage() {
  lcd.clear();
  displayOzoneReading();

  //display cleaning up
  lcd.setCursor(0, 1);
  lcd.print("Regulating Ozone");
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