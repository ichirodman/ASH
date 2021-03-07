#include <Wire.h>
#include <VL53L0X.h>

#define DISCRETE_DISTANCE_UNIT 60
#define MAX_DISCRETE_VALUE 10
#define ON_DISCRETE_DISTANCE_MODE_EXIT 1500


VL53L0X distanceSensor;

void initDistanceSensor() {
    Wire.begin();  
    distanceSensor.setTimeout(600);
    if (!distanceSensor.init()) {
      Serial.println("Failed to detect and initialize sensor! Setup process stopped.");
      while (true) {};
    }
    distanceSensor.startContinuous(400);
}

uint16_t getDistance() {
  uint16_t value = distanceSensor.readRangeContinuousMillimeters();
  if (distanceSensor.timeoutOccurred()) { Serial.print("TIMEOUT"); }
  return value;
}

void listenDistanceDiscrete(void (*onLessDistance) (), void (*onGreaterDistance) (), void (*onFinished) ()) {
  while (getDistance() > 8000) {};
  uint16_t previousStableValue = getDistance();
  uint8_t stableStateCount = 0, switchesAmount = 0;
  while (stableStateCount < 7) {
    uint16_t currentValue = getDistance();

    if (abs(currentValue - previousStableValue) > DISCRETE_DISTANCE_UNIT) {
      stableStateCount = 0;
      previousStableValue = currentValue - currentValue % DISCRETE_DISTANCE_UNIT;
      for (; switchesAmount >= 0 && switchesAmount > previousStableValue / DISCRETE_DISTANCE_UNIT; switchesAmount--) { onLessDistance(); }
      for (; switchesAmount <= MAX_DISCRETE_VALUE && switchesAmount < previousStableValue / DISCRETE_DISTANCE_UNIT; switchesAmount++) { onGreaterDistance(); }
    } else { stableStateCount++; }
  }
  onFinished();
  delay(ON_DISCRETE_DISTANCE_MODE_EXIT);
  dumpGesturesData();
}
