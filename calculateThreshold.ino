void calculateThreshold(){
  const int numSamples = 100;  // Number of samples for calibration
  
  // Collect calibration data
  for (int i = 0; i < numSamples; i++) {
    sensors_event_t event;
    accel.getEvent(&event);
    
    XVal += event.acceleration.x-offsetX;
    YVal += event.acceleration.y-offsetY;
    ZVal += event.acceleration.z-offsetZ;
    
    delay(10);
  }
  
  // Calculate average offset values
  ThresholdAccl = sqrt((XVal/numSamples)*(XVal/numSamples) + (YVal/numSamples)*(YVal/numSamples) + (ZVal/numSamples)*(ZVal/numSamples));
  
  // Print calibration results
  Serial.print("Threshold Calculation complete: ");
  Serial.print("ThresholdAccl: "); Serial.println(ThresholdAccl);

}