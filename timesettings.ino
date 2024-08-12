void timesettings() {
  tft.pushImage(0, 0, 240, 240, TimeSettings);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setFreeFont(FF18);
  tft.setTextSize(0);
  int tt_hh = t_hh;
  if (tt_hh > 12) {
    tt_hh = tt_hh - 12;
  }
  if (t_hh == 0) {
    tft.drawString("0" + String(tt_hh), 25, 96);
  }
  else if (t_hh > 0 && tt_hh < 10) {
    tft.drawString("0" + String(tt_hh), 25, 96);
  } else {
    tft.drawString(String(tt_hh), 25, 96);
  }

  if (t_mm < 10) {
    tft.drawString("0" + String(t_mm), 93, 96);
  } else {
    tft.drawString(String(t_mm), 93, 96);
  }
  if (t_hh < 12) {
    tft.drawString("AM", 164, 96);
  } else {
    tft.drawString("PM", 164, 96);
  }
  if (t_dd < 10) {
    tft.drawString("0" + String(t_dd), 25, 183);
  } else {
    tft.drawString(String(t_dd), 25, 183);
  }
  if (t_mn < 10) {
    tft.drawString("0" + String(t_mn), 93, 183);
  } else {
    tft.drawString(String(t_mn), 93, 183);
  }
  if (t_yr < 2022) {
    t_yr = 2022;
  }
  tft.drawString(String(t_yr), 161, 183);
  if (SubScreen == 0) {
    tft.drawRoundRect(9, 81, 58, 48, 6, Light_Green);
  } else if (SubScreen == 1) {
    tft.drawRoundRect(77, 81, 58, 48, 6, Light_Green);
  } else if (SubScreen == 2) {
    tft.drawRoundRect(9, 168, 58, 48, 6, Light_Green);
  } else if (SubScreen == 3) {
    tft.drawRoundRect(77, 168, 58, 48, 6, Light_Green);
  } else if (SubScreen == 4) {
    tft.drawRoundRect(144, 168, 88, 48, 6, Light_Green);
  } else {
    tft.drawRoundRect(79, 226, 88, 48, 6, Light_Green);
  }
}