void settings() {
  tft.pushImage(0, 0, 240, 240, Settingspage);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setFreeFont(FF18);
  tft.setTextSize(0);
  switch (AutoBright) {
    case 0: tft.drawString("  Auto  ", 80, 100); break;
    case 1: tft.drawString("  20%   ", 85, 100); break;
    case 2: tft.drawString("  40%   ", 85, 100); break;
    case 3: tft.drawString("  60%   ", 85, 100); break;
    case 4: tft.drawString("  80%   ", 85, 100); break;
    case 5: tft.drawString(" 100%   ", 80, 100); break;
  }
  switch (Autoscreen) {
    case 0: tft.drawString("Always On", 65, 185); break;
    case 1: tft.drawString("1 Minute ", 75, 185); break;
    case 2: tft.drawString("2 Minute ", 75, 185); break;
    case 3: tft.drawString("3 Minute ", 75, 185); break;
    case 4: tft.drawString("4 Minute ", 75, 185); break;
    case 5: tft.drawString("5 Minute ", 75, 185); break;
  }

  if (SubScreen == 0) {
    tft.drawRoundRect(16, 85, 208, 48, 6, Light_Green);
  } else if (SubScreen == 1) {
    tft.drawRoundRect(16, 169, 208, 48, 6, Light_Green);
  } else {
    tft.drawRoundRect(66, 225, 108, 48, 6, Light_Green);
  }
}
