#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// is used in many timers
long currentTime = 0;

volatile byte fillPintCounter = 0;
byte fillPintJob = 0;

boolean isFillProcessRunning = false;
boolean isNextProcessRunning = false;
boolean isPumpProcessRunning = false;

boolean isPumpRestricted = false;

byte fillProcessCyclus = 0;
byte nextProcessCyclus = 0;

boolean isInitSetupRunning = true;

byte currentPintMode = -1;
byte lastPintMode = 0;

boolean cancelFlag = false;
byte updateEncoder = false;

// just logos
#include "logoHelper.h"

#include "mmcHelper.h"
#include "loadsHelper.h"

#include "layoutHelper.h"

// global logo variables
loadIcon engineSymbol(1, 39, 0);
loadIcon pumpSymbol(26, 39, 3);

#include "processHelper.h"
#include "routineHelper.h"


void setup()   {
  Serial.begin(9600);
  Serial.print("Start:");


  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);

 /*
    
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
 
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);


   * only test stop
   */
   
  setupDisplay();
  setupMMC();
  setupLoads();

  // startup values
  fillPintCounter = 1;
  isFillProcessRunning = true;
  isInitSetupRunning = true;
}

long printDebugTime = 0;
void printDebug() {

  if (!(millis() > printDebugTime + 500))
    return;

  //Serial.print("Fill Debug: fillPintCounter = ");
  //Serial.print(fillPintCounter, DEC);

  /*
    Serial.print(", isFill.. = ");
    Serial.print(isFillProcessRunning);
    Serial.print(", isNext.. = ");
    Serial.print(isNextProcessRunning);
    Serial.print(", isPump.. = ");
    Serial.print(isPumpProcessRunning);
    Serial.print(", isInit.. = ");
    Serial.print(isInitSetupRunning);
  */

  //Serial.print(", fillProcessCyclus = ");
  //Serial.print(fillProcessCyclus, DEC);

  Serial.print(", nextProcessCyclus = ");
  Serial.print(nextProcessCyclus, DEC);

  Serial.print("\n");

  /*
    Serial.print("Pint Debug: currentPintMode = ");
    Serial.print(currentPintMode, DEC);
    Serial.print(", isNextProcessRunning = ");
    Serial.print(isNextProcessRunning);
    Serial.print(", nextProcessCyclus = ");
    Serial.print(nextProcessCyclus);
    Serial.print("\n");
  */
  printDebugTime = millis();

}

void checkPumpRestriction() {

  if (isPumpRestricted)
    return;

  if (millis() < 30000)
    return;

  isPumpRestricted = true;
  pwmPump = 100;

  // print restricted mark
  display.drawRect(1, 1, 3, 3, 0);

  // force printing
  updateEncoder = true;
}

void loop() {
  
  // print and update all the logos if pump and engine is off
  if ((!pumpSymbol.isOn) && (!engineSymbol.isOn))
    printAll();

  // check mode and logic
  checkMode();

  checkPumpRestriction();

  // debug prints
  //printDebug();
}

