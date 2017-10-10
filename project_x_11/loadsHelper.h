#ifndef LOADS_HELPER
#define LOADS_HELPER

// engine
static int pinPump = 9;
static int pinEngine = 11;
static int pinReed = 15;

//static int pinReed = 7;

// setup
void setupLoads() {
  pinMode(pinPump, OUTPUT);
  pinMode(pinEngine, OUTPUT);
  pinMode(pinReed, INPUT_PULLUP);
}

void globalIconPrint(byte x, byte y, byte iconNum) {
  // engine Icons
  if (iconNum == 0) {
    display.drawBitmap(x, y, logo_enigne0, 16, 16, 1);
  } else if (iconNum == 1) {
    display.drawBitmap(x, y, logo_enigne1, 16, 16, 1);
  } else if (iconNum == 2) {
    display.drawBitmap(x, y, logo_enigne2, 16, 16, 1);

    // pump Icons
  } else if (iconNum == 3) {
    display.drawBitmap(x, y, logo_pump0, 16, 16, 1);
  } else if (iconNum == 4) {
    display.drawBitmap(x, y, logo_pump1, 16, 16, 1);
  } else if (iconNum == 5) {
    display.drawBitmap(x, y, logo_pump2, 16, 16, 1);
  }
  display.display();
}

// base Icon class
class baseIcon
{
  public:
    baseIcon(const byte x, const byte y);

    const byte xPos;
    const byte yPos;
    boolean isFirstTime;
    boolean isOn = false;
    boolean wasOn = false;
    byte currentIcon;
};

baseIcon::baseIcon(const byte x, const byte y)
  : xPos(x), yPos(y)
{
  isFirstTime = true;
  currentIcon = 0;
}

// engine Icon
class loadIcon : public baseIcon
{
  public:
    loadIcon(byte x, byte y, const byte offset);

    long lastPrintTime;
    const byte iconOffset;

    void checkIcon();
    void printIconText();
    
  private:
    void printIconLogo();
};

loadIcon::loadIcon(const byte x, const byte y, const byte offset)
  : baseIcon::baseIcon(x, y), iconOffset(offset)
{
  lastPrintTime = 0;
}

void loadIcon::checkIcon() {
  // check if icon needs to be updated
  if ((isOn != wasOn) || isFirstTime) {
    printIconText();

    // set for the next time
    wasOn = isOn;
  }

  if (isOn || isFirstTime) {
    printIconLogo();
  }

  isFirstTime = false;
}

void loadIcon::printIconText()
{
  // clear rect
  display.fillRect(xPos, yPos + 18, 20, 10, 0);

  // prepare display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(xPos, yPos + 18);

  // print text
  if (isOn) {
    // write lable
    display.println("On");
  } else {
    // write lable
    display.println("Off");
  }

  display.display();
}

void loadIcon::printIconLogo()
{  
  // now print the icon
  if (isOn || isFirstTime) {

    // get system time
    currentTime = millis();

    if ((currentTime - lastPrintTime > 250) || isFirstTime) {
      // clear rect

      display.fillRect(xPos, yPos, 16, 16, 0);

      // global function for logo print
      globalIconPrint(xPos, yPos, currentIcon + iconOffset);

      // increment engine
      if (currentIcon < 2) {
        currentIcon++;
      } else {
        currentIcon = 0;
      }

      lastPrintTime = currentTime;
    }
  }
}

// reed sensor variables
boolean isReedOn = false;
boolean wasReedOn = false;
boolean isFirstPrintReed = true;

void checkReed() {

  // Serial.println("check reed");
  isReedOn = !digitalRead(pinReed);

  //  Serial.println(isReedOn, BIN);

  if (isReedOn != wasReedOn || isFirstPrintReed) {
    //Serial.println("detected reed");
    
    if (isReedOn) {
      display.drawBitmap(46, 60, logo_reedCleaner, 8, 4, 0);
      display.drawBitmap(46, 60, logo_reedClosed, 8, 4, 1);
    } else {
      display.drawBitmap(46, 60, logo_reedCleaner, 8, 4, 0);
      display.drawBitmap(46, 60, logo_reedOpen, 8, 4, 1);
    }
    
    display.display();

    isFirstPrintReed = false;
    wasReedOn = isReedOn;
  }
}

#endif
