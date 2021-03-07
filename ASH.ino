#include "paj7620.h"
#include "Keyboard.h"


bool isWindowsOverviewOpen = false;

void setup() {
  while (!Serial) {};
  Serial.begin(9600);
  initKeyboard();
  initDistanceSensor();
  initLED();
  initGesturesIdentifier();
}


void loop() {
  updateButton();

  uint8_t gesture = getGesture();

  if (isWindowsOverviewOpen) {
    listenDistanceDiscrete([] { primaryShortcut(KEY_LEFT_SHIFT, KEY_TAB); }, [] { primaryShortcut(KEY_TAB); }, [] { primaryShortcut(KEY_RETURN); });
    isWindowsOverviewOpen = false;
  } else {
    if (gesture == GES_UP_FLAG) {
      primaryShortcut(KEY_LEFT_GUI);
      isWindowsOverviewOpen = true;
    } else if (gesture == GES_DOWN_FLAG) {
      primaryShortcut(KEY_ESC);
    } else if (gesture == GES_RIGHT_FLAG) {
      primaryShortcut(KEY_LEFT_ALT, KEY_TAB);
    } else if (gesture == GES_LEFT_FLAG) {
      primaryShortcut(KEY_LEFT_ALT, KEY_LEFT_SHIFT, KEY_TAB);
    } else if (gesture == GES_BACKWARD_FLAG || gesture == GES_FORWARD_FLAG) {
      primaryShortcut(KEY_LEFT_GUI, 'd');
    }
  }
}
