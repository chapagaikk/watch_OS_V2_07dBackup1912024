float updateMovingAverage(float newValue) {
  accelerationWindow[currentIndex] = newValue;
  currentIndex = (currentIndex + 1) % WindowSize;

  float sum = 0.0;
  for (int i = 0; i < WindowSize; i++) {
    sum += accelerationWindow[i];
  }

  return sum / WindowSize;
}