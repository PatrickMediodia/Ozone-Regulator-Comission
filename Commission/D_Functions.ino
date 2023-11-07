void StopSystem() {
  //Turn off ozone emitter
  digitalWrite(Fan_Relay, LOW);

  functionExecuted = true;

  //Stop the timer and the ozone sensor
  vTaskSuspend(H_CheckOzone);
  vTaskSuspend(H_Runtime);

  //if paused is used, and start is ran, it will restart the value of the timer
  timer.pause();

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
  lcd.print("0zone: 5ppm");
}

void displayTimeElapsed() {
  float timeElapsed = (timer.read() / 1000.0) / 60.0;
  int timeElapsedWhole = static_cast<int>(timeElapsed);

  char secondsCount[2];
  float seconds = (timeElapsed - timeElapsedWhole) * 60;
  dtostrf(seconds, 2, 0, secondsCount);
  if (seconds <= 9.99) {
    secondsCount[0] = '0';  
  }

  //display time elapsed
  lcd.setCursor(2, 1);
  lcd.print("Time: ");

  //display minutes
  lcd.setCursor(8, 1);
  lcd.print(timeElapsedWhole);

  lcd.setCursor(9, 1);
  lcd.print(":");

  //display seconds
  lcd.setCursor(10, 1);
  lcd.print(secondsCount);
}