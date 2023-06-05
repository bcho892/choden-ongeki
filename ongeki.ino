#include <Joystick.h>
#include "EC11.hpp"
#define encoderPinA 2
#define encoderPinB A0
#define minMouseX 0
#define maxMouseX 1023
#define buttons 8
#define minValue -1
#define maxValue 10
EC11 encoder;
Joystick_ joystick;

const int buttonPins[] = {A1, A2, A3, 10, 11, 12, 6, 7};
int lastButtonState[] = {0, 0, 0, 0, 0, 0, 0, 0};

void pinDidChange() {
  encoder.checkPins(digitalRead(encoderPinA), digitalRead(encoderPinB));
}

void prepare() {
  joystick.begin();
  joystick.setXAxisRange(minMouseX, maxMouseX);
}

void setup() {
  for (int i = 0; i < buttons; ++i) {
    pinMode(buttonPins[i], INPUT_PULLUP);  // Use internal pull-up resistors
  }
  pinMode(encoderPinA, INPUT_PULLUP);  // Use internal pull-up resistors
  pinMode(encoderPinB, INPUT_PULLUP);  // Use internal pull-up resistors

  prepare();
}

static int value = 0;

void loop() {
  for (int i = 0; i < buttons; ++i) {
    int currentButtonState = !digitalRead(buttonPins[i]);
    if (currentButtonState != lastButtonState[i]) {
      joystick.setButton(i, currentButtonState);
      lastButtonState[i] = currentButtonState;
    }
  }

  EC11Event e;
  if (encoder.read(&e)) {
    if (e.type == EC11Event::StepCW) {
      value -= e.count;
    } else {
      value += e.count;
    }

    // Map the value to the mouse X position range
    int mouseX = map(value, minValue, maxValue, minMouseX, maxMouseX);
    if (mouseX < minValue) {
      mouseX = minValue;
      value = minValue;
    } else if (mouseX > maxMouseX) {
      mouseX = maxMouseX;
      value = maxValue;
    }
    // Set the mouse X position
    joystick.setXAxis(mouseX);
  }
  for (int i = 0; i < 50; i++) {
    encoder.checkPins(digitalRead(encoderPinA), digitalRead(encoderPinB));
    delay(1);
  }
}
