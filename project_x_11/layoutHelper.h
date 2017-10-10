#ifndef LAYOUT_HELPER
#define LAYOUT_HELPER

void setupDisplay() {
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // rect around the display
  //display.drawRect(0, 0, 128, 64, 1);

  // horizontal line under textblock
  display.drawLine(79, 35, 127, 35, WHITE);
  display.drawLine(1, 35, 48, 35, WHITE);

  // draw arrows next to mmc
  display.drawBitmap(46, textBlockPosY, logo_arrowLeft, 8, 8, 1);
  display.drawBitmap(73, textBlockPosY, logo_arrowRight, 8, 8, 1);

  // direction indicator
  display.drawBitmap(79, 47, logo_directionIndic, 8, 16, 1);

  // print filling mark
  display.drawRect(81, 47, 5, 3, 1);

  // print restricted mark
  display.drawRect(1, 1, 3, 3, 1);

}

byte xPosPint = 88;
byte yPosPint = 38;

//currentPintMode = -1;
//lastPintMode = 0;

void checkPint() {
  if (currentPintMode == lastPintMode)
    return;

  // only once
  lastPintMode = currentPintMode;

  //Serial.print("update PintLogo\n");

  if (currentPintMode == 255) {
    // clean the shot because position of pint is unknown
    display.fillRect(xPosPint, yPosPint, 60, 16, 0);
    display.display();

    return;
  }

  //display.drawBitmap(xPosPint, yPosPint, logo_pintCleaner, 16, 16, 0);
  display.drawBitmap(xPosPint, yPosPint, logo_pint0, 16, 16, 1);

  if (!isFillProcessRunning) {

    if (fillPintCounter > 1) {
      display.drawBitmap(xPosPint + 13, yPosPint, logo_halfPintEmpty, 8, 16, 1);
    } else {
      display.drawBitmap(xPosPint + 13, yPosPint, logo_halfPintFull, 8, 16, 0);
    }

    if (fillPintCounter > 2) {
      display.drawBitmap(xPosPint + 19, yPosPint, logo_halfPintEmpty, 8, 16, 1);
    } else {
      display.drawBitmap(xPosPint + 19, yPosPint, logo_halfPintFull, 8, 16, 0);
    }

    if (fillPintCounter > 3) {
      display.drawBitmap(xPosPint + 25, yPosPint, logo_halfPintEmpty, 8, 16, 1);
    } else {
      display.drawBitmap(xPosPint + 25, yPosPint, logo_halfPintFull, 8, 16, 0);
    }

    if (fillPintCounter > 4) {
      display.drawBitmap(xPosPint + 31, yPosPint, logo_halfPintEmpty, 8, 16, 1);
    } else {
      display.drawBitmap(xPosPint + 31, yPosPint, logo_halfPintFull, 8, 16, 0);
    }
  }




  /*
    display.drawBitmap(xPosPint + 13, yPosPint, logo_halfPintEmpty, 8, 16, 1);
    display.drawBitmap(xPosPint + 19, yPosPint, logo_halfPintEmpty, 8, 16, 1);
    display.drawBitmap(xPosPint + 25, yPosPint, logo_halfPintEmpty, 8, 16, 1);
    display.drawBitmap(xPosPint + 31, yPosPint, logo_halfPintEmpty, 8, 16, 1);
  */

  display.display();
}

#endif
