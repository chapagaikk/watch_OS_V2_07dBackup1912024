// long press
void LongPress() {
  
  Serial.println(F("LongPressDetected: "));
  //TouchStartTime = millis() - 1000;  // as set in setPressTicks()
  lastwake = millis();
  lastDisplayUpdate = millis();
  //particleSensor.shutDown();
  if (Screen == 0){
      Screen = 1;       //watchface,settings ...
      SubScreen = 0;
  } else if (Screen == 1) {
    if (SubScreen == 0) {   //watchfaces
      Screen = 2;     //differentwatchfaces
      SubScreen = 0;
    } else if (SubScreen == 1) { //timesettings
      Screen = 3;         //settime, date, month ...
      t_hh = rtc.getHour();
      t_mm = rtc.getMinute();
      t_dd = rtc.getDay();
      t_mn = rtc.getMonth()+1;
      t_yr = rtc.getYear();
      Serial.println(rtc.getMonth());
      Serial.println(t_mn);
      SubScreen = 0;
    } else if (SubScreen == 2) {  //settings
      Screen = 4;
      SubScreen = 0;
      facechange = true;
      Screenchange = true;
    } else if (SubScreen == 3) {    //exitIcon
      Screen = 0;
      SubScreen = 0;      //BacktoScreen0//watchface, HR, Step, Exit
    }

  } else if (Screen == 2) {  
    Screen = 1;
    SubScreen = 0;
  } else if (Screen == 3) {
    if (SubScreen == 0) {
      t_hh++;
      if (t_hh > 23) {
        t_hh = 0;
      }
    } else if (SubScreen == 1) {
      t_mm++;
      if (t_mm > 59) {
        t_mm = 0;
      }
    } else if (SubScreen == 2) {
      t_dd++;
      if (t_dd > 31) {
        t_dd = 0;
      }
    } else if (SubScreen == 3) {
      t_mn++;
      if (t_mn > 12) {
        t_mn = 1;
      }
    } else if (SubScreen == 4) {
      t_yr++;
      if (t_yr > 2041) {
        t_yr = 2022;
      }
    } else {
      rtc.setTime(0, t_mm, t_hh, t_dd, t_mn, t_yr);
      Screen = 1;
      SubScreen = 1;
    }
  } else if (Screen == 4) {
    if (SubScreen == 0) {
      AutoBright++;
      if (AutoBright > 5) {
        AutoBright = 0;
      }
      if (AutoBright > 0) {
        analogWrite(LCD_BACKLIGHT, AutoBright * 50);
      }
      EEPROM.write(2, AutoBright);
      EEPROM.commit();
    } else if (SubScreen == 1) {
      Autoscreen++;
      if (Autoscreen > 5) {
        Autoscreen = 0;
      }
      EEPROM.write(1, Autoscreen);
      EEPROM.commit();
    } else if (SubScreen == 2) {
      Screen = 1;
      SubScreen = 2;
    }
  } /*else if ((Screen == 5) || (Screen == 6)) {
    Screen = 0;
    SubScreen = 0;
    } else if (Screen == 7) {
    Screen = 1;
    SubScreen = 3;
   }*/

  Serial.print("Screen ");
  Serial.println(Screen);
  Serial.print("Sub ");
  Serial.println(SubScreen);

  facechange = true;
  Screenchange = true;
  pressstate = 1;
  lastpressed = millis();
}