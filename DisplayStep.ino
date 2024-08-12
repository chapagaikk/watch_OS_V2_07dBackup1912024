void DisplayStep(){  
  
  tft.setTextColor(TFT_CYAN, colour7);
  tft.setCursor(90, 120);
  tft.loadFont(FONT_SMALL);
  tft.print("STEPS");

  tft.setCursor(90, 90);
  tft.loadFont(FONT_LARGE);
  tft.print(stepCount);

  img.pushRotated(0);
}