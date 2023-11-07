void T_CheckOzone(void *pvParameters) {
  (void) pvParameters;
  while (1) {
    OzoneState = digitalRead(OzoneSensor);
    if (OzoneState == HIGH) {
      //turn off ozone emitter
      digitalWrite(Fan_Relay, HIGH);
    } else {
      //turn on ozone emitter
      digitalWrite(Fan_Relay, LOW);
    }

    //Display(OzoneState);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void T_CheckRunningStatus(void *pvParameters) {
  (void) pvParameters;

  while (1) {
    StartState = digitalRead(BTN_Start);
    StopState = digitalRead(BTN_Stop);

    if (StartState == HIGH && StopState == LOW){
      lcd.clear();

      vTaskResume(H_CheckOzone);
      vTaskResume(H_Runtime);

      //start the timer when button has been pushed
      timer.start();
    }

    if (StartState == LOW && StopState == HIGH){
      StopSystem();  
    }
    functionExecuted = false;
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void T_Runtime(void *pvParameters) {
  (void) pvParameters;
  while (1) {
    displayOzoneReading();
    displayTimeElapsed();

    if (timer.read() >= duration && !functionExecuted) {
      StopSystem();
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}