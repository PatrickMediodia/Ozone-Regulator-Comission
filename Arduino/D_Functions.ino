void StopSystem() {
  //Turn off ozone emitter
  digitalWrite(Fan_Relay, LOW);

  functionExecuted = true;

  //Stop the timer and the ozone sensor
  vTaskSuspend(H_CheckOzone);
  vTaskSuspend(H_Runtime);

  //if paused is used, and start is ran, it will restart the value of the timer
  timer.pause();
}

void Display(int sensorReading) {
  //lcd.setCursor(2, 0);
  //lcd.print("Ozone Reading");
}