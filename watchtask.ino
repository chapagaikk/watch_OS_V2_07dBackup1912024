void watchtask() {
  
  //timeClient.update();
  if (pressstate == 1 && digitalRead(2) == 1) {
    pressstate = 0;
    Serial.println("Am i In PressState1???");
  }
  if (AutoBright == 0) {
    unsigned int lv = 50; //constrain(lightMeter.readLightLevel(), 50, 500);
    analogWrite(LCD_BACKLIGHT, lv / 2);
  }
  /*if (!detectingPulse){
    pox.shutdown();
    detectStep();
  }*/
  /*if (Autoscreen != 0 && millis() - lastwake > Autoscreen * 60000) {
    analogWrite(LCD_BACKLIGHT, 0);
    delay(1000);

    tft.fillScreen(colour7);
    Serial.print("ESP Going to Sleep:AutoScreen/Millis:  ");
    Serial.print(Autoscreen);
    Serial.println(millis() - lastwake > Autoscreen * 60000);

    //gpio_deep_sleep_hold_en();
    //gpio_hold_en((gpio_num_t)LCD_BACKLIGHT);
    //esp_deep_sleep_start();
  }*/
  if (Screen == 0) {
    if (SubScreen == 0) {
      //Serial.println("Going to watchfacedsp");
      //Serial.print("Watch Face: ");
      //Serial.print(watchface);
      //facechange = true;
      //pox.shutdown();
      particleSensor.shutDown();
      watchfacedsp();
    } else if (SubScreen == 1) {
      //pox.shutdown();
      particleSensor.shutDown();
      DisplayStep();
    } else {
      //pox.setOnBeatDetectedCallback(onBeatDetected);
      //pox.resume();
      particleSensor.wakeUp();
      img.fillSprite(colour7);  //Clear the display
      //tft.pushImage(0, 0, 240, 240, hr1);
      detectingPulse = true;
      HRApp();
      detectingPulse = false;
    }

  } else if (Screen == 1 && Screenchange == true) {
    if (SubScreen == 0) {
      tft.pushImage(0, 0, 240, 240, facechangeicon);
    } else if (SubScreen == 1) {
      tft.pushImage(0, 0, 240, 240, timeseticon);
    } else if (SubScreen == 2) {
      tft.pushImage(0, 0, 240, 240, settingsicon);
    //} else if (SubScreen == 3) {
    //  tft.pushImage(0, 0, 240, 280, gamesicon);
    } else if (SubScreen == 3) {
      tft.pushImage(0, 0, 240, 240, exiticon);
    }
  } else if (Screen == 2 && Screenchange == true) {
    watchfacedsp();
    Screenchange = false;
    }else if (Screen == 3 && Screenchange == true) {
    timesettings();
    Screenchange = false;
  } else if (Screen == 4 && Screenchange == true) {
    settings();
    Screenchange = false;
  } else if (Screen == 3 && millis() - lastpressed > 2000 && millis() - lastvaluechange > 500 && pressstate == 1) {
    if (SubScreen == 0) {
      t_hh++;
      if (t_hh > 23) {
        t_hh = 0;
      }
      facechange = true;
      Screenchange = true;
    } else if (SubScreen == 1) {
      t_mm++;
      if (t_mm > 59) {
        t_mm = 0;
      }
      facechange = true;
      Screenchange = true;
    } else if (SubScreen == 2) {
      facechange = true;
      Screenchange = true;
      t_dd++;
      if (t_dd > 31) {
        t_dd = 0;
      }
    } else if (SubScreen == 3) {
      t_mn++;
      if (t_mn > 12) {
        t_mn = 1;
      }
      facechange = true;
      Screenchange = true;
    } else if (SubScreen == 4) {
      t_yr++;
      if (t_yr > 2041) {
        t_yr = 2024;
      }
      facechange = true;
      Screenchange = true;
    }
    lastvaluechange = millis();
  }
}