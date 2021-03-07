#include "GyverButton.h"

#define BUTTON_PIN 5


GButton button(BUTTON_PIN, LOW_PULL, NORM_OPEN);

void updateButton() { button.tick(); }

void isSingleButtonPress() { return button.isSingle(); }

void isDoubleButtonPress() { return button.isDouble(); }

void isTripleButtonPress() { return button.isTriple(); }
