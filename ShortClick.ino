// this function will be called for short click.

void ShortClick() {
  Serial.println("singleClick() detected.");
  lastwake = millis();
  ///////////////// SCREEN 0 (SubScreen 0,1,2)//////////////////////////////
  if (Screen == 0) {
    SubScreen++;    //clockface, HRApp, Compass
    if (SubScreen > 2) { //0-Clock, 1-Step, 2-Pulse,3-Exit
      SubScreen = 0;
      //facechange = true;
    }
  /*  if (SubScreen == 1) {
      //particleSensor.wakeUp();
    } else {
      //particleSensor.shutDown();
    }*/
  } else if (Screen == 1) { //clock,timesetting,setting,exit.
    SubScreen++;
    if (SubScreen > 3) {
      SubScreen = 0;
    }
    Screenchange = true;

  } else if (Screen == 2) { 
    watchface++;
    if (watchface > 4) {
      watchface = 0;
    }
    EEPROM.write(0, watchface);
    EEPROM.commit();
    facechange = true;      //Changes in the WatchFaces
    Screenchange = true;

  } else if (Screen == 3) {
    SubScreen++;
    if (SubScreen > 5) {
      SubScreen = 0;
    }
    Screenchange = true;
  } else if (Screen == 4) {
    SubScreen++;
    if (SubScreen > 2) {
      SubScreen = 0;
    }
    Screenchange = true;
  } /*else if (Screen == 5) {
    detectStep();
  } else if (Screen == 6) {
    HRApp();
  } else if (Screen == 7) {
    Screen = 5;
    Screenchange = true;
  }*/

  Serial.print("Sub ");
  Serial.println(SubScreen);
  tft.fillScreen(colour7);
  pressstate = 1;
  facechange = true;
  lastDisplayUpdate = millis();
  lastpressed = millis();
}  // ShortClick