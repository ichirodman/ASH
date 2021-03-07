#include <time.h>
#include "paj7620.h"

#define GESTURE_UPDATING_INTERVAL 200
#define COMPLICATED_GES_QUIT_TIME 2000

#define GI_NONE -1
#define GI_ERROR -2


uint8_t lastGestureType = GI_NONE;
auto timeToUpdate = millis() + GESTURE_UPDATING_INTERVAL;
bool dumpNextGesture = false;

void initGesturesIdentifier() {
    uint8_t error = paj7620Init();
    if (error) {
        Serial.print("Paj7620 init ERROR, CODE : ");
        Serial.println(error);
    } else { Serial.println("Paj7620 init OK"); }
}

uint8_t getGesture() {
  if (lastGestureType != GI_NONE) { lastGestureType = GI_NONE; }
  if (millis() > timeToUpdate) { 
    timeToUpdate = millis() + GESTURE_UPDATING_INTERVAL;
    gestureUpdateThreadFunction();
    if (dumpNextGesture) {
      dumpNextGesture = false;
      lastGestureType = GI_NONE;
    }
    if (lastGestureType == GES_FORWARD_FLAG || lastGestureType == GES_BACKWARD_FLAG || lastGestureType == GES_CLOCKWISE_FLAG || lastGestureType == GES_COUNT_CLOCKWISE_FLAG) {
      dumpGesturesData();
      timeToUpdate += COMPLICATED_GES_QUIT_TIME;
    }
  }
  return lastGestureType;
}

void gestureUpdateThreadFunction() {
    static auto getProcessedGesture = [] () -> uint8_t { 
      uint8_t data = 0, data1 = 0, data2 = 0, error = paj7620ReadReg(0x43, 1, &data);
      if (!error) {
          if (data == GES_LEFT_FLAG || data == GES_RIGHT_FLAG || data == GES_UP_FLAG || data == GES_DOWN_FLAG) {
              paj7620ReadReg(0x43, 1, &data1); return data1 == GES_FORWARD_FLAG || data1 == GES_BACKWARD_FLAG ? data1 : data;
          } else if (data == GES_FORWARD_FLAG || data == GES_BACKWARD_FLAG || data == GES_CLOCKWISE_FLAG || data == GES_COUNT_CLOCKWISE_FLAG) {
              return data;
          } else { paj7620ReadReg(0x44, 1, &data2); return data2 == GES_WAVE_FLAG ? GES_WAVE_FLAG : GI_NONE; }
      } else {return GI_ERROR; }
    };
    lastGestureType = getProcessedGesture();
}

void dumpGesturesData() { dumpNextGesture = true; }
