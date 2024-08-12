void calibrateSensor() {
  const int numSamples = 100;  // Number of samples for calibration
  
  offsetX = 0;
  offsetY = 0;
  offsetZ = 0;
  
  // Collect calibration data
  for (int i = 0; i < numSamples; i++) {
    sensors_event_t event;
    accel.getEvent(&event);
    
    offsetX += event.acceleration.x;
    offsetY += event.acceleration.y;
    offsetZ += event.acceleration.z;
    
    delay(10);
  }
  
  // Calculate average offset values
  offsetX /= numSamples;
  offsetY /= numSamples;
  offsetZ /= numSamples;
  
  // Print calibration results
  Serial.print("Calibration complete. OffsetX: ");
  Serial.print(offsetX);
  Serial.print(", OffsetY: ");
  Serial.print(offsetY);
  Serial.print(", OffsetZ: ");
  Serial.println(offsetZ);
}