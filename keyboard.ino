#include "Keyboard.h"


void initKeyboard() {
    Keyboard.begin();  
}

void primaryShortcut(char modifier) { primaryShortcut(modifier, NULL); }

void primaryShortcut(char modifier, char keyChar) { primaryShortcut(modifier, NULL, keyChar); }

void primaryShortcut(char firstModifier, char secondModifier, char keyChar) {
    if (firstModifier != NULL) { Keyboard.press(firstModifier); }
    if (secondModifier != NULL) { Keyboard.press(secondModifier); }
    if (keyChar != NULL) { Keyboard.press(keyChar); }
    sysLightLED();
    delay(50);
    Keyboard.releaseAll();
    delay(70);
    clearLED();
}
