#ifndef PROCESS_HELPER
#define PROCESS_HELPER


byte pwmPump = 150;
const byte pwmEngine = 63;
const byte pwmEngineManuel = 63;

boolean isRunnigTillReed = false;

// this is just a startup value change pump time in pumpprocess
int processPumpTime = 300;

int processEngineTime = 1000;

// debounce for start/stop process
long debounceStartStopTime = 0;
long startPumpTime = 0;
long startEngineTime = 0;

long debounceNextTime = 0;
long debouncePumpTime = 0;

// if pint counter is 0
void checkManualMode() {
  if (isFillProcessRunning)
    return;

  if (!digitalRead(pinLeft)) {
    // tell icon to update next time

    if(!pumpSymbol.isOn) {
      //Serial.print("print that text");      
      pumpSymbol.isOn = true;
      pumpSymbol.checkIcon();
    }
    
    pumpSymbol.isOn = true;
    analogWrite(pinPump, pwmPump);
  } else {
    pumpSymbol.isOn = false;
    analogWrite(pinPump, 0);
  }

  if (!digitalRead(pinRight)) {
    // tell icon to update next time

    if(!engineSymbol.isOn) {
      //Serial.print("print that text");      
      engineSymbol.isOn = true;
      engineSymbol.checkIcon();
    }

    engineSymbol.isOn = true;
    analogWrite(pinEngine, pwmEngineManuel);

    // do not know where the pint is
    currentPintMode = 255;
  } else {
    engineSymbol.isOn = false;
    analogWrite(pinEngine, 0);
  }
}

boolean isCancelPressed() {
  // return if not pressed
  if (digitalRead(pinRight))
    return false;

  if (!(millis() > debounceStartStopTime + 500))
    return false;

  if (!(millis() > debounceNextTime + 500))
    return false;

  if (!(millis() > debouncePumpTime + 500))
    return false;

  //Serial.print("Cancel!\n");

  // turn everything off
  engineSymbol.isOn = false;
  analogWrite(pinEngine, 0);
  pumpSymbol.isOn = false;
  analogWrite(pinPump, 0);

  // press right ends routine und resets
  //fillPintCounter = 0; // no reset to pos 0

  nextProcessCyclus = 0;
  fillProcessCyclus = 0;

  isFillProcessRunning = false;
  isPumpProcessRunning = false;
  isNextProcessRunning = false;
  isInitSetupRunning = false;

  cancelFlag = true;

  // do not know where the pint is
  currentPintMode = 255;
  fillPintJob = 0;

  // set debounce variable
  debounceStartStopTime = millis();

  updateEncoder = true;

  // next = 0
  return true;
}

boolean pumpOnTimer() {
  // start the pump and capture time

  if (startPumpTime == 0) {
    startPumpTime = millis();

    // no pumping while init
    if (!isInitSetupRunning) {
      pumpSymbol.isOn = true;

      // update pump once
      pumpSymbol.checkIcon();
      
      analogWrite(pinPump, pwmPump);
    }
  }

  if (!(millis() > startPumpTime + processPumpTime))
    return false ;

  pumpSymbol.isOn = false;
  analogWrite(pinPump, 0);

  // returns true when done
  return true;
}

boolean runEngineTillReed(boolean reedState) {

  // to set the engine only once
  if (!isRunnigTillReed) {
    isRunnigTillReed = true;

    engineSymbol.isOn = true;

    // update engineSymbol once
    engineSymbol.checkIcon();

    analogWrite(pinEngine, pwmEngine);
  }

  // return loop because no reed event yet
  if (digitalRead(pinReed) == reedState) {
    return false;
    delay(10);
  }

  // no switch off the engine
  //engineSymbol.isOn = false;
  //analogWrite(pinEngine, 0);

  isRunnigTillReed = false;
  return true;
}

boolean runEngineOnTimer() {

  // start the engine and capture time
  if (startEngineTime == 0) {
    startEngineTime = millis();

    engineSymbol.isOn = true;

    // update engineSymbol once
    engineSymbol.checkIcon();

    analogWrite(pinEngine, pwmEngine);
  }


  if (!(millis() > startEngineTime + processEngineTime))
    return false;

  engineSymbol.isOn = false;
  analogWrite(pinEngine, 0);

  startEngineTime = 0;
  return true;
}

void printAll() {

  checkReed();
  checkPintWheel();
  checkPint();

  printEncoder();
  printMmc();

  engineSymbol.checkIcon();
  pumpSymbol.checkIcon();

}

#endif
