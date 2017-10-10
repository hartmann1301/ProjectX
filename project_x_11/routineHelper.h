#ifndef ROUTINE_HELPER
#define ROUTINE_HELPER



void nextPintRoutine() {

  if (!isNextProcessRunning)
    return;

  // extra round after cancel pressed
  if (cancelFlag) {
    cancelFlag = false;

    if (nextProcessCyclus == 1)
      nextProcessCyclus = 0;
  }


  if (nextProcessCyclus == 0) {

    if (!runEngineTillReed(false))
      return;

    // next cyclus
    nextProcessCyclus = 1;
    isRunnigTillReed = false;

    // run wheel on timer cyclus
  } else if (nextProcessCyclus == 1) {

    if (!runEngineTillReed(true))
      return;

    // next cyclus
    nextProcessCyclus = 2;

    // run wheel on timer cyclus
  } else if (nextProcessCyclus == 2) {

    if (!runEngineOnTimer())
      return;

    // next cyclus
    nextProcessCyclus = 0;

    // decrement one pint and order reprint
    //Serial.print("Done Next Routine!\n");
    isNextProcessRunning = false;

    currentPintMode = 99;
    updateEncoder = true;
  }
}

void fillPintRoutine() {

  if (isNextProcessRunning || isPumpProcessRunning)
    return;

  if (!isFillProcessRunning)
    return;

  // pump on Timer cyclus
  if (fillProcessCyclus == 0) {

    if (!pumpOnTimer())
      return;

    // next cyclus
    fillProcessCyclus = 1;
    startPumpTime = 0;

    // run wheel to reed cyclus
  } else if (fillProcessCyclus == 1) {

    if (!runEngineTillReed(true))
      return;

    // next cyclus
    fillProcessCyclus = 2;

    // run wheel on timer cyclus
  } else if (fillProcessCyclus == 2) {

    if (!runEngineOnTimer())
      return;

    // next cyclus
    fillProcessCyclus = 0;

    // decrement one pint and order reprint
    fillPintCounter -= 1;
    updateEncoder = true;

    // if pint is last do not return here
    if (fillPintCounter != 0)
      return;

    // stop filling process if this was the last pin
    isFillProcessRunning = false;
    isInitSetupRunning = false;

    // know i know where my pint is
    currentPintMode = 99;

    processPumpTime = 1500;

  }

}

void checkStartRoutine() {
  if (isNextProcessRunning || isFillProcessRunning || isPumpProcessRunning)
    return;

  if (!digitalRead(pinRight)) {

    if (fillPintCounter == 1) {
      // pint pos 1

      if (!(millis() > debounceNextTime + 500))
        return;

      //Serial.print("Start Next Routine!\n");
      isNextProcessRunning = true;
      nextProcessCyclus = 0;
      isRunnigTillReed = false;
      fillPintJob = fillPintCounter;

      // set debounce variable
      debounceNextTime = millis();
      updateEncoder = true;
    } else {
      // pint pos is 2-5
      if (!(millis() > debounceStartStopTime + 500))
        return;

      if (!(millis() > debounceNextTime + 500))
        return;

      if (currentPintMode == 255) {
        //Serial.print("Start Next Routine on 2-5!\n");
        isNextProcessRunning = true;
        nextProcessCyclus = 0;
        isRunnigTillReed = false;

        debounceNextTime = millis();
      } else {
        //Serial.print("Start Fill Routine!\n");
        isFillProcessRunning = true;
        fillProcessCyclus = 0;
        startPumpTime = 0;

        debounceStartStopTime = millis();

      }
      updateEncoder = true;

    }
  }

  if (!digitalRead(pinLeft)) {

    if (fillPintCounter == 1) {
      // pint pos 1

      if (!(millis() > debouncePumpTime + 500))
        return;

      if (currentPintMode != 255) {
        //Serial.print("Start Pump Routine!\n");
        isPumpProcessRunning = true;
        startPumpTime = 0;

        updateEncoder = true;

        // set debounce variable
        debouncePumpTime = millis();
      }
    }

  }
}

void pumpProcessRoutine() {
  if (isFillProcessRunning || isNextProcessRunning)
    return;

  if (!isPumpProcessRunning)
    return;

  // pump the timer
  if (!pumpOnTimer())
    return;

  //Serial.print("Pump Routine Done!\n");

  // cyclus done
  isPumpProcessRunning = false;
  updateEncoder = true;
}

void checkMode() {

  // manueller Mode
  if (fillPintCounter == 0) {
    checkManualMode();
    return;
  }

  // check if nextProcess should start
  checkStartRoutine();

  // check if this is on
  nextPintRoutine();
  pumpProcessRoutine();
  fillPintRoutine();

  if (isCancelPressed())
    return;

}
#endif
