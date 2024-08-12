void detectStep(){
  
  sensors_event_t event;
  accel.getEvent(&event);

  XVal = event.acceleration.x- offsetX;
  YVal = event.acceleration.y- offsetY;
  ZVal = event.acceleration.z- offsetZ;

  //Serial.print("XVal: ");Serial.print(XVal);  Serial.print(" "); Serial.print("YVal: ");  Serial.print(YVal); Serial.print(" "); 
  //Serial.print("ZVal: ");  Serial.println(ZVal);
  // Calculate magnitude of acceleration
  float acceleration = sqrt(XVal * XVal + YVal * YVal + ZVal * ZVal);
  delay(10);

  //Serial.print("acceleration: "); Serial.println(acceleration);
  // Update adaptive threshold
  float movingAverage = updateMovingAverage(acceleration);
  //threshold = movingAverage * ThresholdMultiplier;
  //Serial.print("threshold: "); Serial.println(threshold);

  // Check for step event
  if (acceleration > threshold) {
    if (readingsBelowThreshold > StepCompletionThreshold) {
      stepCount++;
      Serial.print("Step count: ");
      Serial.println(stepCount);
      
      readingsBelowThreshold = 0;
    }
  } else {
    readingsBelowThreshold++;
  }
}