// pulse measurement
void HRApp() {

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  while (1){
    long irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true) {     //We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();
      beatsPerMinute = 60 / (delta / 1000.0);
      Serial.println("//We sensed a beat!");

      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
        rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
        rateSpot %= RATE_SIZE; //Wrap variable
        Serial.println("//Take average of readings, Averaging: ");
        Serial.println(AveragingTime);

        AveragingTime++;
        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;

        //tft.fillScreen(TFT_BLACK);  //Clear the display
        img.fillSprite(TFT_BLACK);
        tft.pushImage(0, 0, 240, 240, hr2);
        tft.setTextColor(TFT_CYAN, TFT_BLACK);
        tft.loadFont(FONT_LARGE);
        tft.setCursor(100, 100);
        tft.print(beatAvg);
        tft.setCursor(100, 140);
        tft.loadFont(FONT_SMALL);
        tft.print(" BPM ");
        img.pushRotated(0);

      }
    }

    Serial.print("IR=");
    Serial.print(irValue);
    Serial.print(", BPM=");
    Serial.print(beatsPerMinute);
    Serial.print(", Avg BPM=");
    Serial.print(beatAvg);

    if (irValue < 50000){
      img.fillSprite(TFT_BLACK);
      tft.pushImage(0, 0, 240, 240, hr1);
      tft.setCursor(60, 130);    
      tft.loadFont(FONT_SMALL);
      tft.print("NO FINGER");
      Serial.print(" No finger?");
    }
    Serial.println();
    //delay(500);

    if (AveragingTime > 30){
    particleSensor.shutDown();
    SubScreen = 0;
    Serial.print("SubScreen"); Serial.println(SubScreen);
    break;
    }
  }
  return;
  /*if (millis() - tsLastReport > REPORTING_PERIOD_MS){
    //pox.update();
    //img.fillSprite(colour7);  //Clear the display
    //img.pushImage(0, 0, 240, 240, hr2);
    int BeatValue = pox.getHeartRate();
    int Spo2Value = pox.getSpO2();

    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.loadFont(FONT_LARGE);
    tft.setCursor(80, 90);
    tft.print(BeatValue);
    tft.setCursor(90, 120);
    tft.loadFont(FONT_SMALL);
    tft.print(" BPM ");
    tft.loadFont(FONT_LARGE);
    tft.setCursor(80, 135);
    tft.print(Spo2Value);
    tft.setCursor(90, 165);
    tft.loadFont(FONT_SMALL);
    tft.print(" % ");

    //img.pushRotated(0);

    Serial.print("HeartRate: ");
    Serial.print(BeatValue);
    Serial.print("SPO2: ");
    Serial.println(Spo2Value);

    tsLastReport = millis();
    AveragingTime++;
    
  }
  pox.update();
  /*  if (AveragingTime>100){
    AveragingTime = 0;
    pox.shutdown();
    detectingPulse = false;
  }*/

  // send to the device using the Bluetooth 
  //SerialBT.print(" Avg Beat: ");
  //SerialBT.println(beatAvg);  */
  
}
