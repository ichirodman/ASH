#include "FastLED.h"

#define DEFAULT_BLINK_DURATION 1000
#define LED_PIN 4
#define LED_BRIGHTNESS 5
#define MIN_BLINK_INTERVAL 300

#define WAIT_COLOR 0xFF0000
#define SYS_COLOR 0xFFFFFF
#define COLOR_WHITISH_BLUE 0x00FFFF
#define COLOR_BLUE 0x0000FF
#define COLOR_VIOLET 0xFF00FF
#define COLOR_GREEN 0x00FF00
#define COLOR_YELLOW 0xFFFF00


CRGB led_values[1];
int const userModesAmount = 4;
unsigned long modeColors[userModesAmount] = {COLOR_BLUE, COLOR_VIOLET, COLOR_GREEN, COLOR_YELLOW};

void initLED() {
  FastLED.addLeds<WS2811, LED_PIN , GRB>(led_values, 1).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(LED_BRIGHTNESS);
  clearLED();
}

void lightLED(unsigned long colorRGB) { led_values[0] = CRGB(colorRGB); FastLED.show(); }

void clearLED() { FastLED.clear(); FastLED.show(); }

void sysLightLED() { lightLED(SYS_COLOR); }

void userModeLightLED(uint8_t modeIndex) { lightLED(modeColors[modeIndex % userModesAmount]); }
