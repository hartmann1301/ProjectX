#ifndef MMC_HELPER
#define MMC_HELPER

// define pins
static int pinInt0 = 2; // hardware interrupt pin is digital pin 2
static int pinInt1 = 3; // hardware interrupt pin is digital pin 3
static int pinLeft = 5;
static int pinRight = 4;

volatile byte encoderPos = 0;
volatile byte oldEncPos = -1;

// prototypes
void isrInt0();
void isrInt1();

const byte encoderPosX = 59;
const byte encoderPosY = 41;

const byte mmcPosX = 56;
const byte mmcPosY = 0;
const byte mmcWidth = 16;
const byte mmcHeight = 32;

volatile byte currentLogoMMC = 0;
volatile byte newLogoMMC = -1;

const int xPosPintWheel = 48;
const int yPosPintWheel = 32;

const int textBlockPosY = 12;
const int textLineHeight = 9;

// setup
void setupMMC() {
  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);

  // interrupts
  pinMode(pinInt0, INPUT_PULLUP);
  pinMode(pinInt1, INPUT_PULLUP);
  attachInterrupt(0, isrInt0, CHANGE);
  attachInterrupt(1, isrInt1, CHANGE);
}

void printMmc() {
  // check current position for newLogoMMC
  if (!digitalRead(pinLeft)) {
    if (encoderPos % 2 == 0) {
      newLogoMMC = 1;
    } else {
      newLogoMMC = 2;
    }
  } else if (!digitalRead(pinRight)) {
    if (encoderPos % 2 == 0) {
      newLogoMMC = 3;
    } else {
      newLogoMMC = 4;
    }
  } else {
    if (encoderPos % 2 == 0) {
      newLogoMMC = 5;
    } else {
      newLogoMMC = 6;
    }
  }

  if (newLogoMMC != currentLogoMMC) {
    // clear currentLogoMMC
    display.fillRect(mmcPosX, mmcPosY, mmcWidth, mmcHeight, 0);

    //Serial.print(" print new mmcLogo ");
    //Serial.println(newLogoMMC);

    if (newLogoMMC == 1) {
      display.drawBitmap(mmcPosX, mmcPosY, logo_mmcLeft0, mmcWidth, mmcHeight, 1);
    } else if (newLogoMMC == 2) {
      display.drawBitmap(mmcPosX, mmcPosY, logo_mmcLeft1, mmcWidth, mmcHeight, 1);
    } else if (newLogoMMC == 3) {
      display.drawBitmap(mmcPosX, mmcPosY, logo_mmcRight0, mmcWidth, mmcHeight, 1);
    } else if (newLogoMMC == 4) {
      display.drawBitmap(mmcPosX, mmcPosY, logo_mmcRight1, mmcWidth, mmcHeight, 1);
    } else if (newLogoMMC == 5) {
      display.drawBitmap(mmcPosX, mmcPosY, logo_mmcFront0, mmcWidth, mmcHeight, 1);
    } else if (newLogoMMC == 6) {
      display.drawBitmap(mmcPosX, mmcPosY, logo_mmcFront1, mmcWidth, mmcHeight, 1);
    } else {
      //Serial.print("Error unknown logo");
    }
    // say display to show changes !!!!
    display.display();

    // set currentLogoMMC for next check
    currentLogoMMC = newLogoMMC;
  }

}

void checkPintWheel() {

  // delete olds
  display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 16, logo_way5f, 16, 16, 0);
  display.drawBitmap(xPosPintWheel + 4, yPosPintWheel + 16, logo_way4f, 16, 16, 0);
  display.drawBitmap(xPosPintWheel, yPosPintWheel + 8, logo_way3f, 16, 16, 0);
  display.drawBitmap(xPosPintWheel + 4, yPosPintWheel, logo_way2f, 16, 16, 0);
  display.drawBitmap(xPosPintWheel + 16, yPosPintWheel, logo_way1f, 16, 16, 0);

  display.drawBitmap(xPosPintWheel + 25, yPosPintWheel + 13, logo_wheelPinF, 8, 8, 0);
  display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 25, logo_wheelPinF, 8, 8, 0);
  display.drawBitmap(xPosPintWheel + 2, yPosPintWheel + 19, logo_wheelPinF, 8, 8, 0);
  display.drawBitmap(xPosPintWheel + 3, yPosPintWheel + 4, logo_wheelPinF, 8, 8, 0);
  display.drawBitmap(xPosPintWheel + 18, yPosPintWheel + 1, logo_wheelPinF, 8, 8, 0);

  // print new
  if (fillPintCounter == 0) {
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 16, logo_way5e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel + 16, logo_way4e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel, yPosPintWheel + 8, logo_way3e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel, logo_way2e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel, logo_way1e, 16, 16, 1);

    display.drawBitmap(xPosPintWheel + 25, yPosPintWheel + 13, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 25, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 2, yPosPintWheel + 19, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 3, yPosPintWheel + 4, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 18, yPosPintWheel + 1, logo_wheelPinE, 8, 8, 1);

  } else if (fillPintCounter == 1) {
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 16, logo_way5e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel + 16, logo_way4e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel, yPosPintWheel + 8, logo_way3e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel, logo_way2e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel, logo_way1f, 16, 16, 1);

    display.drawBitmap(xPosPintWheel + 25, yPosPintWheel + 13, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 25, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 2, yPosPintWheel + 19, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 3, yPosPintWheel + 4, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 18, yPosPintWheel + 1, logo_wheelPinE, 8, 8, 1);

  } else if (fillPintCounter == 2) {
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 16, logo_way5e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel + 16, logo_way4e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel, yPosPintWheel + 8, logo_way3e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel, logo_way2f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel, logo_way1f, 16, 16, 1);

    display.drawBitmap(xPosPintWheel + 25, yPosPintWheel + 13, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 25, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 2, yPosPintWheel + 19, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 3, yPosPintWheel + 4, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 18, yPosPintWheel + 1, logo_wheelPinF, 8, 8, 1);

  } else if (fillPintCounter == 3) {
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 16, logo_way5e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel + 16, logo_way4e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel, yPosPintWheel + 8, logo_way3f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel, logo_way2f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel, logo_way1f, 16, 16, 1);

    display.drawBitmap(xPosPintWheel + 25, yPosPintWheel + 13, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 25, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 2, yPosPintWheel + 19, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 3, yPosPintWheel + 4, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 18, yPosPintWheel + 1, logo_wheelPinF, 8, 8, 1);

  } else if (fillPintCounter == 4) {
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 16, logo_way5e, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel + 16, logo_way4f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel, yPosPintWheel + 8, logo_way3f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel, logo_way2f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel, logo_way1f, 16, 16, 1);

    display.drawBitmap(xPosPintWheel + 25, yPosPintWheel + 13, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 25, logo_wheelPinE, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 2, yPosPintWheel + 19, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 3, yPosPintWheel + 4, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 18, yPosPintWheel + 1, logo_wheelPinF, 8, 8, 1);

  } else if (fillPintCounter == 5) {
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 16, logo_way5f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel + 16, logo_way4f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel, yPosPintWheel + 8, logo_way3f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 4, yPosPintWheel, logo_way2f, 16, 16, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel, logo_way1f, 16, 16, 1);

    display.drawBitmap(xPosPintWheel + 25, yPosPintWheel + 13, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 16, yPosPintWheel + 25, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 2, yPosPintWheel + 19, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 3, yPosPintWheel + 4, logo_wheelPinF, 8, 8, 1);
    display.drawBitmap(xPosPintWheel + 18, yPosPintWheel + 1, logo_wheelPinF, 8, 8, 1);
  }
  display.display();
}

void printTextLine(byte num, String text) {

  // set defaults normal, they should already be set
  display.setTextSize(1);
  display.setTextColor(WHITE);

  byte tab;

  byte leftInt = 3;
  byte rightInt = 82;


  if (num == 0 || num == 2) {
    // upper line
    tab = 0;
    if (num == 0) {
      display.fillRect(rightInt * tab + leftInt, textBlockPosY - 5, 42, textLineHeight, 0);
      display.setCursor(rightInt * tab + leftInt, textBlockPosY - 5);
      display.println(text);
    } else {
      display.fillRect(rightInt * tab + leftInt, textBlockPosY + 5, 42, textLineHeight, 0);
      display.setCursor(rightInt * tab + leftInt, textBlockPosY + 5);
      display.println(text);
    }

  } else if (num == 1 || num == 3) {
    // lower line
    tab = 1;
    if (num == 1) {
      display.fillRect(rightInt * tab + leftInt, textBlockPosY - 5, 42, textLineHeight, 0);
      display.setCursor(rightInt * tab + leftInt, textBlockPosY - 5);
      display.println(text);
    } else {
      display.fillRect(rightInt * tab + leftInt, textBlockPosY + 5, 42, textLineHeight, 0);
      display.setCursor(rightInt * tab + leftInt, textBlockPosY + 5);
      display.println(text);
    }
  }

  display.display();
}

void checkTextLines() {
  // need to be in routine

  //Serial.print("checkTextLines!\n");

  if (isInitSetupRunning) {
    printTextLine(0, "");
    printTextLine(2, "");

    printTextLine(1, " Stop");
    printTextLine(3, " Init");
    return;
  }

  if (fillPintCounter == 0) {
    printTextLine(0, " Hand");
    printTextLine(2, "Pumpen");

    printTextLine(1, " Hand");
    printTextLine(3, "Drehen");

  } else if (fillPintCounter == 1) {

    // left side
    if (isFillProcessRunning) {
      printTextLine(0, "");
      printTextLine(2, "");
    } else {
      if (isPumpProcessRunning) {
        printTextLine(0, " Wait");
        printTextLine(2, "(Pump)");
      } else {
        if (currentPintMode != 255) {
          printTextLine(0, " Pump");
          printTextLine(2, "1 Shot");
        } else {
          printTextLine(0, "Unknown");
          printTextLine(2, " Pos.");
        }
      }
    }

    // right side
    if (isNextProcessRunning || isFillProcessRunning) {
      if (isNextProcessRunning) {
        printTextLine(1, " Stop");
        printTextLine(3, " Next");
      } else {
        printTextLine(1, " Stop");
        printTextLine(3, "Routine");
      }
    } else {
      printTextLine(1, " Next");
      printTextLine(3, " Shot");
    }

  } else {
    // left side
    printTextLine(0, "");
    printTextLine(2, "");

    // right side
    if (currentPintMode == 255) {
      // pin unknown
      if (isNextProcessRunning) {
        printTextLine(1, " Stop");
        printTextLine(3, " Next");
      } else {
        printTextLine(1, "Search");
        printTextLine(3, " Shot");
      }
    } else {
      // pin known, start routine
      if (isFillProcessRunning) {
        printTextLine(1, " Stop");
        printTextLine(3, "Routine");
      } else {
        printTextLine(1, " Start");
        printTextLine(3, "Routine");
      }
    }
  }
}

void printEncoder() {
  // or if running
  //if (oldEncPos != encoderPos) {

  if (oldEncPos != encoderPos || updateEncoder) {
    //Serial.println(encoderPos);

    // this repaints the logo on process change
    updateEncoder = false;

    // clear rect
    display.fillRect(encoderPosX, encoderPosY, 12, 16, 0);

    // print new one
    display.setCursor(encoderPosX, encoderPosY);
    display.setTextColor(WHITE);
    display.setTextSize(2);

    // print the pints to fill, "-" on start
    if (isInitSetupRunning) {
      display.println("-");
    } else {
      display.println(fillPintCounter);
    }

    // updates the pints wheel
    checkPintWheel();

    // updates the texts left and right to the wheel
    checkTextLines();

    display.display();
    oldEncPos = encoderPos;

    // clear rect left down
    display.fillRect(90, 56, 44, 8, 0);

    // print status line
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(90, 56);

    if (isInitSetupRunning) {
      display.println("Wait");
      return;
    }

    if (fillPintCounter == 0) {
      display.println("Man.");
    } else if (fillPintCounter == 1) {
      display.println("Shot");
    } else if (fillPintCounter > 1) {
      display.println("Shots");
    }
  }
}

void incEncoder() {
  // overflowing encoder position
  if (encoderPos >= 5) {
    encoderPos = 0;
  } else {
    encoderPos++;
  }

  // increment pints if possible
  if (fillPintCounter < 5) {

    if (isFillProcessRunning)
      return;

    fillPintCounter++;

    if (currentPintMode != 255)
      currentPintMode = fillPintCounter;
  }

  // repaint the mmc und stuff
  updateEncoder = true;
}

void decEncoder() {
  // overflowing encoder position
  if (encoderPos <= 0) {
    encoderPos = 5;
  } else {
    encoderPos--;
  }

  // decrement pints if possible
  if (fillPintCounter > 0) {

    if (isFillProcessRunning)
      return;

    fillPintCounter--;

    if (currentPintMode != 255)
      currentPintMode = fillPintCounter;
  }

  // repaint the mmc und stuff
  updateEncoder = true;
}

void isrInt0() {
  cli();
  if (PIND & B00000100) {    // read pin2
    // rising edge on Pin 2
    //Serial.print("rising edge on Pin 2");
    if (PIND & B00001000) {  // read pin3
      incEncoder();
    } else {
      decEncoder();
    }
  } else {
    // falling edge on Pin 2
    //Serial.print("falling edge on Pin 2");
    if (PIND & B00001000) {  // read pin3
      decEncoder();
    } else {
      incEncoder();
    }
  }
  sei();
}

void isrInt1() {
  cli();
  if (PIND & B00001000) {    // read pin3
    // rising edge on Pin 3
    //Serial.print("rising edge on Pin 3");
    if (PIND & B00000100) {  // read pin3
      decEncoder();
    } else {
      incEncoder();
    }
  } else {
    // falling edge on Pin 3
    //Serial.print("falling edge on Pin 3");
    if (PIND & B00000100) {  // read pin3
      incEncoder();
    } else {
      decEncoder();
    }
  }
  sei(); //restart interrupts
}
#endif /* _Adafruit_SSD1306_H_ */
