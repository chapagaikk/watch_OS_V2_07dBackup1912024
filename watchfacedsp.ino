void watchfacedsp() {

  if (facechange) {
    tft.fillScreen(TFT_BLACK);

    if (watchface == 1) {
      tft.setTextSize(0);
      tft.pushImage(0, 0, 240, 240, Casio2);
      tft.setTextColor(0x0081, background);
      tft.fillRoundRect(48, 127, 128, 48, 5, background);
      Serial.print("Watch Face: ");
      Serial.println(watchface);

    } else if (watchface == 2) {
      tft.setTextSize(0);
      tft.pushImage(0, 0, 240, 240, Casio1);
      tft.setTextColor(0x0081, background);
      tft.fillRoundRect(48, 127, 128, 48, 5, background);
      Serial.print("Watch Face: ");
      Serial.println(watchface);

    } else if (watchface == 4) {
      tft.pushImage(0, 0, 240, 240, cdface1);
      img2.pushImage(0, 0, 240, 100, cdface11);
      tft.setTextColor(TFT_WHITE);
      tft.setFreeFont(FF18);
      tft.setTextSize(2);
      Serial.print("Watch Face: ");
      Serial.println(watchface);
    }
    facechange = false;
    lastfacechange = millis();
  }

  /////////////////////////////////////////////////////////////////
  ////// WATCH FACE 0  ///////////////////////////////////////////
  ////////////////////////////////////////////////////////////////
  if (watchface == 0) {
    Serial.print("Watch Face: ");
    Serial.println(watchface);    
    int b = 0;
    int b2 = 0;
    for (int i = 0; i < 360; i++) {
      x[i] = (r * cos(rad * i)) + ssx;
      y[i] = (r * sin(rad * i)) + ssy;
      px[i] = ((r - 16) * cos(rad * i)) + ssx;
      py[i] = ((r - 16) * sin(rad * i)) + ssy;

      lx[i] = ((r - 26) * cos(rad * i)) + ssx;
      ly[i] = ((r - 26) * sin(rad * i)) + ssy;

      if (i % 30 == 0) {
        start[b] = i;
        b++;
      }

      if (i % 6 == 0) {
        startP[b2] = i;
        b2++;
      }
    }
    rAngle = rAngle - 2;
    angle = rtc.getSecond() * 6;
    s = String(rtc.getSecond());
    m = String(rtc.getMinute());
    h = String(rtc.getHour());
    if (m.toInt() < 10)
      m = "0" + m;
    if (h.toInt() < 10)
      h = "0" + h;
    if (s.toInt() < 10)
      s = "0" + s;

    if (rtc.getDay() > 10) {
      d1 = rtc.getDay() / 10;
      d2 = rtc.getDay() % 10;
    } else {
      d1 = "0";
      d2 = String(rtc.getDay());
    }

    if (rtc.getMonth() > 10) {
      m1 = rtc.getMonth() / 10;
      m2 = rtc.getMonth() % 10;
    } else {
      m1 = "0";
      m2 = String(rtc.getMonth());
    }
    if (angle >= 360)
      angle = 0;
    if (rAngle <= 0)
      rAngle = 359;
    if (dir == 0)
      circle = circle + 0.5;
    else
      circle = circle - 0.5;
    if (circle > 140)
      dir = !dir;

    if (circle < 100)
      dir = !dir;
    if (angle > -1) {
      lastAngle = angle;

      VALUE = ((angle - 270) / 3.60) * -1;
      if (VALUE < 0)
        VALUE = VALUE + 100;

      img.fillSprite(TFT_BLACK);
      img.fillCircle(ssx, ssy, 124, TFT_BLACK);
      img.setTextColor(TFT_WHITE, TFT_BLACK);
      img.drawString(days[rtc.getDayofWeek()], circle, 140, 2);

      for (int i = 0; i < 12; i++)
        if (start[i] + angle < 360) {
          img.drawString(cc[i], x[start[i] + angle], y[start[i] + angle], 2);
          img.drawLine(px[start[i] + angle], py[start[i] + angle], lx[start[i] + angle], ly[start[i] + angle], color1);
        } else {
          img.drawString(cc[i], x[(start[i] + angle) - 360], y[(start[i] + angle) - 360], 2);
          img.drawLine(px[(start[i] + angle) - 360], py[(start[i] + angle) - 360], lx[(start[i] + angle) - 360], ly[(start[i] + angle) - 360], color1);
        }
      img.setFreeFont(&DSEG7_Modern_Bold_20);
      img.drawString(s, ssx, ssy - 36);
      img.setFreeFont(&DSEG7_Classic_Regular_28);
      img.drawString(h + ":" + m, ssx, ssy + 28);
      img.setTextFont(0);

      img.fillRect(70, 86, 12, 20, color3);
      img.fillRect(84, 86, 12, 20, color3);
      img.fillRect(150, 86, 12, 20, color3);
      img.fillRect(164, 86, 12, 20, color3);

      img.setTextColor(0x35D7, TFT_BLACK);
      img.drawString("MONTH", 84, 78);
      img.drawString("DAY", 162, 78);
      img.setTextColor(TFT_SKYBLUE, TFT_BLACK);
      img.drawString("CST", 120, 194);
      img.drawString("***", 120, 124);
      img.setTextColor(TFT_WHITE, color3);
      img.drawString(m1, 77, 96, 2);
      img.drawString(m2, 91, 96, 2);
      img.drawString(d1, 157, 96, 2);
      img.drawString(d2, 171, 96, 2);
      for (int i = 0; i < 60; i++)
        if (startP[i] + angle < 360)
          img.fillCircle(px[startP[i] + angle], py[startP[i] + angle], 1, color1);
        else
          img.fillCircle(px[(startP[i] + angle) - 360], py[(startP[i] + angle) - 360], 1, color1);
      img.fillTriangle(ssx - 1, ssy - 70, ssx - 5, ssy - 56, ssx + 4, ssy - 56, TFT_ORANGE);
      img.fillCircle(px[rAngle], py[rAngle], 6, TFT_RED);
      img.pushSprite(0, 0);
    }
  } else if (rtc.getSecond() != lastsec || Screen == 3) {
    if (watchface == 1 || watchface == 2) {
      String med;
      if (rtc.getSecond() % 2) {
        med = ":";
      } else {
        med = " ";
      }
      tft.setFreeFont(&DSEG7_Classic_Bold_30);
      if (rtc.getHour() > 10 && rtc.getMinute() > 10) {
        tft.drawString(String(rtc.getHour()) + ":" + String(rtc.getMinute()), 46, 136);
      } else if (rtc.getHour() < 10 && rtc.getMinute() > 10) {
        tft.drawString("0" + String(rtc.getHour()) + ":" + String(rtc.getMinute()), 46, 136);
      } else if (rtc.getHour() > 10 && rtc.getMinute() < 10) {
        tft.drawString(String(rtc.getHour()) + ":0" + String(rtc.getMinute()), 46, 136);
      } else {
        tft.drawString("0" + String(rtc.getHour()) + ":0" + String(rtc.getMinute()), 46, 136);
      }
      tft.setFreeFont(&DSEG7_Classic_Bold_20);
      if (rtc.getSecond() < 10) {
        tft.drawString("0" + String(rtc.getSecond()), 154, 146);
      } else {
        tft.drawString(String(rtc.getSecond()), 154, 146);
      }
      tft.setFreeFont(&DSEG14_Classic_Bold_18);
      tft.drawString(days1[rtc.getDayofWeek()], 94, 106);
      tft.drawString(String(rtc.getDay()), 156, 106);
    } 
    
    ///////////////////////////////////////////////////////////////////////////////////
    /////////////Watch Face 3 ////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    
    else if (watchface == 3) {
      Serial.print("Watch Face: ");
      Serial.println(watchface);
      img.setTextColor(TFT_WHITE, TFT_BLACK);  // Adding a background colour erases previous text automatically
      // Draw clock face
      img.fillCircle(120, 140, 118, TFT_GREEN);
      img.fillCircle(120, 140, 110, TFT_BLACK);
      // Draw 12 lines
      for (int i = 0; i < 360; i += 30) {
        sx = cos((i - 90) * 0.0174532925);
        sy = sin((i - 90) * 0.0174532925);
        x0 = sx * 114 + 120;
        yy0 = sy * 114 + 140;
        x1 = sx * 100 + 120;
        yy1 = sy * 100 + 140;
        img.drawLine(x0, yy0, x1, yy1, TFT_GREEN);
      }
      // Draw 60 dots
      for (int i = 0; i < 360; i += 6) {
        sx = cos((i - 90) * 0.0174532925);
        sy = sin((i - 90) * 0.0174532925);
        x0 = sx * 102 + 120;
        yy0 = sy * 102 + 140;
        // Draw minute markers
        img.drawPixel(x0, yy0, TFT_WHITE);
        // Draw main quadrant dots
        if (i == 0 || i == 180) img.fillCircle(x0, yy0, 2, TFT_WHITE);
        if (i == 90 || i == 270) img.fillCircle(x0, yy0, 2, TFT_WHITE);
      }
      img.fillCircle(120, 141, 3, TFT_WHITE);
      // Pre-compute hand degrees, x & y coords for a fast screen update
      sdeg = rtc.getSecond() * 6;                      // 0-59 -> 0-354
      mdeg = rtc.getMinute() * 6 + sdeg * 0.01666667;  // 0-59 -> 0-360 - includes seconds
      hdeg = rtc.getHour() * 30 + mdeg * 0.0833333;    // 0-11 -> 0-360 - includes minutes and seconds
      hx = cos((hdeg - 90) * 0.0174532925);
      hy = sin((hdeg - 90) * 0.0174532925);
      mx = cos((mdeg - 90) * 0.0174532925);
      my = sin((mdeg - 90) * 0.0174532925);
      sx = cos((sdeg - 90) * 0.0174532925);
      sy = sin((sdeg - 90) * 0.0174532925);
      if (rtc.getSecond() == 0 || initial) {
        initial = 0;
        // Erase hour and minute hand positions every minute
        img.drawLine(ohx, ohy, 120, 141, TFT_BLACK);
        ohx = hx * 62 + 121;
        ohy = hy * 62 + 141;
        img.drawLine(omx, omy, 120, 141, TFT_BLACK);
        omx = mx * 84 + 120;
        omy = my * 84 + 141;
      }
      // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
      img.drawLine(osx, osy, 120, 141, TFT_BLACK);
      osx = sx * 90 + 121;
      osy = sy * 90 + 141;
      img.drawLine(osx, osy, 120, 141, TFT_RED);
      img.drawLine(ohx, ohy, 120, 141, TFT_WHITE);
      img.drawLine(omx, omy, 120, 141, TFT_WHITE);
      img.drawLine(osx, osy, 120, 141, TFT_RED);
      img.fillCircle(120, 141, 3, TFT_RED);
      img.pushSprite(0, 0);
      
    } 
  ///////////////////////////////////////////////////////////////////////////////////
  /////////////Watch Face 4 || 5 ////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////

    else if (watchface == 4) {
      img1.setTextColor(TFT_WHITE, TFT_BLACK);
      img1.setFreeFont(FF24);
      img1.fillSprite(TFT_BLACK);
      //img1.setTextSize(2);

      if (rtc.getHour() > 9 && rtc.getMinute() > 9) {
        img1.drawString(String(rtc.getHour()) + ":" + String(rtc.getMinute()), 66, 30);
      } else if (rtc.getHour() < 10 && rtc.getMinute() > 9) {
        img1.drawString("0" + String(rtc.getHour()) + ":" + String(rtc.getMinute()), 66, 30);
      } else if (rtc.getHour() > 9 && rtc.getMinute() < 10) {
        img1.drawString(String(rtc.getHour()) + ":0" + String(rtc.getMinute()), 66, 30);
      } else {
        img1.drawString("0" + String(rtc.getHour()) + +":0" + String(rtc.getMinute()), 66, 30);
      }
      img1.setFreeFont(FF22);
      if (rtc.getSecond() < 10) {
        img1.drawString("0" + String(rtc.getSecond()), 190, 40);
      } else {
        img1.drawString(String(rtc.getSecond()), 190, 40);
      }
      img1.drawString(days1[rtc.getDayofWeek()] + " " + String(rtc.getDay()) + " " + String(rtc.getYear()), 54, 0);
      //img1.drawString(String(rtc.getDay()), 156, 0);
      img2.pushSprite(0, 180);
      img1.pushSprite(0, 180, TFT_BLACK);
    }
    lastsec = rtc.getSecond();
  }
}