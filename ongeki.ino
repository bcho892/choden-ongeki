#include <Joystick.h>

Joystick_ joystick;

const int buttonPins[] = {A1, A2, A3, 10, 11, 12};
const int buttons = 6;
int lastButtonState[] = {0, 0, 0, 0, 0, 0};

void setup() {
  for (int i = 0; i < buttons; ++i) {
    pinMode(buttonPins[i], INPUT_PULLUP);  // Use internal pull-up resistors
  }
  joystick.begin();
}

void loop() {
  for (int i = 0; i < buttons; ++i) {
    int currentButtonState = !digitalRead(buttonPins[i]);
    if (currentButtonState != lastButtonState[i]) {
      joystick.setButton(i, currentButtonState);
      lastButtonState[i] = currentButtonState;
    }
  }

  delay(50);
}
