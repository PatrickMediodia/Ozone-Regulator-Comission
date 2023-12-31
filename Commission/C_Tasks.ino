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

    else if (StartState == LOW && StopState == HIGH){
      stopAndRegulateOzone = true;
    }

    vTaskDelay(150 / portTICK_PERIOD_MS);
  }
}

void T_CheckOzone(void *pvParameters) {
  (void) pvParameters;
  while (1) {
    //read ozone value
    //returns ppb, converted to ppm as needed
    ozoneReading = Ozone.readOzoneData(COLLECT_NUMBER) / 1000.0;

    if (maxSafeOzoneReached) {
        // if now safe, start emitter on next run of task
        if (ozoneReading <= minimumValue) {
          maxSafeOzoneReached = false;
        } else {
          //turn off emitter, turn on fan
          digitalWrite(OzoneEmitter, HIGH);
          digitalWrite(CarbonFilter, LOW);
        }
    } else {
      // if unsafe, turn off emitter on next run of task
      if (ozoneReading >= maximumValue) {
        maxSafeOzoneReached = true;
      } else {
        //turn on emitter, turn off fan
        digitalWrite(OzoneEmitter, LOW);
        digitalWrite(CarbonFilter, HIGH);
      }
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void T_Runtime(void *pvParameters) {
  (void) pvParameters;
  while (1) {
    if (timer.read() >= duration || stopAndRegulateOzone == true) {
      StopSystem();
    } else {
      displayOzoneReading();
      displayTimeElapsed();
    }

    vTaskDelay(900 / portTICK_PERIOD_MS);
  }
}